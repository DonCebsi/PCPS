import { Injectable } from '@angular/core';
import { HttpClient, HttpHeaders, HttpParams } from '@angular/common/http';
import { Observable } from 'rxjs/Rx';
import 'rxjs/add/operator/map';

import { HttpObservable } from './HttpObservable';
import { PlantDetail } from './PlantDetail';
import { PlantPrev } from './PlantPrev';
import { PlantTemplate } from './PlantTemplate';
import { Node } from './Node';

@Injectable({
	providedIn: 'root'
})
export class DataService {
	
	constructor(private http: HttpClient) { }
	
	getPlant(id: string): HttpObservable<PlantDetail>{
		return new HttpObservable<PlantDetail>('/api/plants/'+id, {}, 3000, this.http);
	}
	
	getPlants(): HttpObservable<PlantPrev[]> {
		return new HttpObservable<PlantPrev[]>('/api/plants', {}, 1000, this.http);
	}

	deletePlant(name: string){
		let options = { headers: new HttpHeaders({'Content-Type':  'application/json'}) };
		this.http.delete<string>('/api/plants/'+name, options).subscribe();
	}

	createPlant(data){
		let options = { headers: new HttpHeaders({'Content-Type':  'application/json'}) };
		this.http.post<string>('/api/plants/'+data.name, data, options).subscribe();
	}
	
	deployPlant(node, plant){
		let options = { headers: new HttpHeaders({'Content-Type':  'application/json'}) };
		this.http.post<string>('/api/nodes/'+node, {plant: plant}, options).subscribe();
	}
	
	getNodes(): HttpObservable<Node[]>{
		return new HttpObservable<Node[]>('/api/nodes', {}, 2000, this.http);
	}
	
	deleteTemplate(name: string){
		let options = { headers: new HttpHeaders({'Content-Type':  'application/json'}) };
		this.http.delete<string>('/api/templates/'+name, options).subscribe();
	}
	
	getTemplates(): HttpObservable<PlantTemplate[]>{
		return new HttpObservable<PlantTemplate[]>('/api/templates', {}, 1000, this.http);
	}
	
	createTemplate(data) {
		let options = { headers: new HttpHeaders({'Content-Type':  'application/json'}) };
		this.http.post<string>('/api/templates/'+data.name, data, options).subscribe();
	}
	
	importPlant(data: any, override: boolean = true) {
		let options = { headers: new HttpHeaders({'Content-Type':  'application/json'}) };
		if(override)
			this.http.put<string>('/api/plant/'+data.name, data, options).subscribe();
		else
			this.http.post<string>('/api/plant/'+data.name, data, options).subscribe();
	}
}