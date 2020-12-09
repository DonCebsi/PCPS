import { Component, Input, Output, OnInit, OnDestroy, EventEmitter } from '@angular/core';
import { ISubscription } from "rxjs/Subscription";

import { DataService } from '../data.service';
import { PlantDetail } from '../PlantDetail';
import { PlantTemplate } from '../PlantTemplate';
import { HttpObservable } from '../HttpObservable';

@Component({
	selector: 'plant-creator',
	templateUrl: './plant-creator.component.html',
	styleUrls: ['./plant-creator.component.css']
})
export class PlantCreatorComponent implements OnInit, OnDestroy {
	/* Display options */
	_showDialog: boolean = false;
	@Output()
	showDialogChange = new EventEmitter();
	
	templateCreator: boolean = false;
	
	plantName: string;
	templates: PlantTemplate[];
	templatesObsv: HttpObservable<PlantTemplate[]>;
	templatesSubscr: ISubscription;
	templateSelect: string;
	
	template: PlantTemplate = {
		name: '',
		/* General */
		maxSize: 1,
		growSpeed: 1,
		regenerationSpeed: 1,
		/* Temperature */
		tempRange: {
			min: 1,
			max: 1
		},
		tempBoost: {
			susceptibility: 1,
			range: 1,
			amount: 1,
			optimum: 1
		},
		/* Moisture */
		moistureThreshold: 1,
		moistureStruggleSeconds: 1,
		moistureLackSusceptibility: 1,
		waterCanGetAboveGround: true,
		/* Humidity */
		humidityRange: {
			min: 1,
			max: 1
		},
		humidityBoost: {
			susceptibility: 1,
			range: 1,
			amount: 1,
			optimum: 1
		},
		/* Light */
		darkMaxSeconds: 1,
		lightMaxSeconds: 1,
		darkLightThreshold: 1,
		lightBoost: {
			susceptibility: 1,
			range: 1,
			amount: 1,
			optimum: 1
		},
		darkSusceptibility: 1
	};
	
	constructor(private service: DataService) {
		console.log(this.template.maxSize);
	}
	
	set showDialog(value){
		if(value)this.templatesSubscr = this.service.getTemplates().subscribe(data => {this.templates=data;});
		else this.templatesSubscr.unsubscribe();
		this._showDialog = value;
		this.showDialogChange.emit(this._showDialog);
	}
	
	@Input()
	get showDialog(){
		return this._showDialog;
	}
	
	ngOnInit() {
	}
	
	ngOnDestroy() {
	}
	
	templateValidate(): boolean {
		let inputs = document.getElementById('template-creator').getElementsByTagName('input');
		for(let i = 0; i < inputs.length; i++){
			if(!inputs[i].validity.valid) return false;
		}
		return true;
	}
	
	templateSubmit() {
		if(!this.templateValidate()) return;
		this.service.createTemplate(this.template);
		this.templateCreator = false;
	}
	
	plantSubmit() {
		let nameInput:any = document.getElementById('plant-name');
		let templateInput:any = document.getElementById('plant-template');
		if(nameInput.validity.valid && templateInput.validity.valid){	
			this.service.createPlant({
				name: this.plantName,
				template: this.templateSelect
			});
			this.showDialog = false;
		}
	}
	
	templateDelete() {
		this.service.deleteTemplate(this.templateSelect);
	}
	
	track(index, item) {
		return JSON.stringify(item);
	}
}
