import { ActivatedRoute } from '@angular/router';
import { Component, OnInit, OnDestroy, Input, Output, EventEmitter } from '@angular/core';
import { DatePipe } from '@angular/common';
import { ISubscription } from "rxjs/Subscription";
import { Chart } from 'chart.js';

import { DataService } from '../data.service';
import { PlantDetail } from '../PlantDetail';
import { HttpObservable } from '../HttpObservable';
import { Node } from '../Node';
import * as config from '../config'

@Component({
	selector: 'plant-detail',
	templateUrl: './plant-detail.component.html',
	styleUrls: ['./plant-detail.component.css'],
	providers: [DatePipe]
})

export class PlantDetailComponent implements OnInit, OnDestroy {
	name: string;
	
	nodes: Node[] = [];
	nodesSubscr: ISubscription;
	nodesObsv: HttpObservable<Node[]>
	
	plant: PlantDetail;
	plantSubscr: ISubscription;
	plantObsv: HttpObservable<PlantDetail>;
	httpErrorCode = -1;
	httpErrorMessage = "<h2>Waiting for Backend...</h2>";
	
	chart;
	
	nodeSelect: string;
	
	_showDeployDiag: boolean = false;
	_timeMin: number;
	_timeMax: number;
	_limit: number;
	timeMinChange = new EventEmitter();
	timeMaxChange = new EventEmitter();
	samplesChange = new EventEmitter();
	showDeployDiagChange = new EventEmitter();
	
	set showDeployDiag(value: boolean) {
		console.log('change');
		if(value){
			this.nodesObsv = this.service.getNodes();
			this.nodesSubscr = this.nodesObsv.subscribe(
				(data: Node[]) => {
					this.nodes = data;
					console.log(this.nodes);
				}
			);
		} else {
			this.nodesSubscr.unsubscribe();
		}
		this._showDeployDiag = value;
	}
	get	showDeployDiag() {
		return this._showDeployDiag;
	}
	
	set timeMin(value: number) {
		this._timeMin = value;
		this.timeMinChange.emit(this._timeMin);
		this.updateFilter();
	}
	get timeMin(): number {
		return this._timeMin;
	}
	
	set timeMax(value: number) {
		this._timeMax = value;
		this.timeMaxChange.emit(this._timeMax);
		this.updateFilter();
	}
	get timeMax(): number {
		return this._timeMax;
	}
	
	set limit(value: number){
		this._limit = value;
		this.samplesChange.emit(this._limit);
		this.updateFilter();
	}
	get limit(): number {
		return this._limit;
	}
	
	constructor(private route:   ActivatedRoute,
	            private service: DataService,
				private datePipe: DatePipe) { }
	
	ngOnInit() {
		this.name = this.route.snapshot.paramMap.get('id');
		this.chart = new Chart('canvas', config.CHART_CONFIG);
		this.plantObsv = this.service.getPlant(this.name);
		console.log('SUBSCRIBE PLANT')
		this.plantSubscr = this.plantObsv.subscribe(
			(data: PlantDetail) => {
				this.httpErrorCode = null;
				this.plant = data;
				// Update chart
				this.updatePlant();
			},
			error => {
				this.httpErrorCode = error.status;
				switch(this.httpErrorCode){
					case 404:
						this.httpErrorMessage = `
							<img style="width: 500px; max-width: 100%;" src="/assets/plant_gone_placeholder.svg"><br>
							<h2>Woops... The plant seems to be gone!</h2>
						`;
						break;
					case 503:
						this.httpErrorMessage = `
							<h2>Lost connection to backed.</h2>
						`;
						break;
					default:
						this.httpErrorMessage = `
							<h2>Unexpected Error ${this.httpErrorCode}:</h2>
							${error.message}
						`;
				}
			}
		);
	}
	
	ngOnDestroy() {
		this.plantSubscr.unsubscribe();
		console.log('UNSUBSCRIBE PLANT')
		if(this.chart) this.chart.destroy();
	}
	
	updatePlant() {
		// Update chart
		for(let i in this.chart.data.datasets){
			let label: string = this.chart.data.datasets[i].label;
			this.chart.data.datasets[i] = Object.assign(
				this.chart.data.datasets[i] || {},
				{ data: this.plant[label] }
			);
		}
		this.chart.data.labels = this.plant.timestamps.map(x => this.datePipe.transform(x, "dd.MM.yy HH:mm:ss"));
		this.chart.update();
	}
	
	updateFilter() {
		console.log('change');
		this.plantObsv.setParams({
			timeMax: this._timeMax,
			timeMin: this._timeMin,
			limit: this._limit
		});
	}
	
	deploy() {
		if(this.nodeSelect){
			this.service.deployPlant(this.nodeSelect, this.name);
			this.showDeployDiag = false;
		}
	}
	
	export() {
		window.open('/api/plants/'+this.name+'?backup');
	}
	
	delete() {
		if (confirm('Are you sure you want to delete this Plant?')) {
			this.service.deletePlant(this.name);
		}
	}
	
	trackNodes(index, item) {
		return JSON.stringify(item);
	}
}
