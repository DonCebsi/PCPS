import { Component, OnInit } from '@angular/core';

import { DataService } from '../data.service';

@Component({
	selector: 'plant-import',
	templateUrl: './plant-import.component.html',
	styleUrls: ['./plant-import.component.css']
})
export class PlantImportComponent implements OnInit {
	
	showDialog = false;
	plant: any = null;
	override: boolean = false;
	
	constructor(private service: DataService) { }
		
	ngOnInit() {
	}
	
	fileChange(event) {
		let input = event.target;
		if(input.files && input.files[0]) {
			let reader = new FileReader();
			let that = this;
			reader.onload = function (e) {
				let plantString: string = <string>(<any> e.target).result;
				try {
					that.plant = JSON.parse(plantString);
				} catch(err) {
					alert('Invalid file format!');
					input.value=null;
					that.plant = null;
				}
			};
			
			reader.readAsText(input.files[0]);
		}
	}
	
	import() {
		if(this.plant === null) return;
		this.service.importPlant(this.plant, this.override);
		this.showDialog = false;
	}
}
