import { Component, OnInit, OnDestroy }      from '@angular/core';
import { Observable } from 'rxjs/Rx';
import { ISubscription } from "rxjs/Subscription";

import { DataService } from '../data.service';
import { PlantPrev }   from '../PlantPrev'

@Component({
	selector: 'plant-list',
	templateUrl: './plant-list.component.html',
	styleUrls: ['./plant-list.component.css']
})

export class PlantListComponent implements OnInit, OnDestroy {
	updater: number = 0;
	plants: PlantPrev[] = [];
	plantsSubscr: ISubscription;
	httpErrorCode: number = -1;
	httpErrorMessage = "<h2>Waiting for Backend...</h2>"
	
	constructor(private service: DataService) { }
	
	ngOnInit() {
		this.plantsSubscr = this.service.getPlants().subscribe(
			data => {
				this.httpErrorCode = null;
				this.plants = data;
			},
			error => {
				this.httpErrorCode = error.status;
				switch(this.httpErrorCode){
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
		console.log(this.plants);
	}
	
	ngOnDestroy() {
		this.plantsSubscr.unsubscribe();
	}
	
	track(index, item) {
		return JSON.stringify(item);
	}
}