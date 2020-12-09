import { Inject } from '@angular/core';
import { HttpClient, HttpParams } from '@angular/common/http';
import { Observable } from 'rxjs/Rx';
import 'rxjs/add/operator/map';

export class HttpObservable<T> extends Observable<T> {
	params = {};
	errorHandler = null;
	successHandler = null;
	
	constructor(private url: string, private staticPrams: any, private interval: number, private http: HttpClient) {
		super(
			observer => {
				let updater;
				let update = () => {
					console.log(this.params);
					if(observer.closed) clearInterval(updater);
					this.http.get<T>(encodeURI(this.url), { params: this.params }).subscribe(
						(data: T) => {
							observer.next(data);
						},
						error => {
							if(this.errorHandler) this.errorHandler(error);
						}
					)
				};
				update();
				updater = setInterval(update, this.interval);
			}
		);
		this.setParams();
	}
	
	public subscribe(success, error?){
		this.errorHandler = error;
		return super.subscribe(success, error);
	}
	
	public setParams(params = {}) {
		this.params = Object.assign(this.staticPrams, params);
	}
}