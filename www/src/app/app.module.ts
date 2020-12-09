import { BrowserModule } from '@angular/platform-browser';
import { NgModule } from '@angular/core';
import { HttpClientModule, HTTP_INTERCEPTORS } from '@angular/common/http';
import { FormsModule } from '@angular/forms';

import { AppComponent } from './app.component';
import { PlantDetailComponent } from './plant-detail/plant-detail.component';
import { PlantListComponent } from './plant-list/plant-list.component';
import { AppRoutingModule } from './app-routing.module';
import { PlantCreatorComponent } from './plant-creator/plant-creator.component';
import { PlantImportComponent } from './plant-import/plant-import.component';

@NgModule({
	declarations: [
		AppComponent,
		PlantDetailComponent,
		PlantListComponent,
		PlantCreatorComponent,
		PlantImportComponent
	],
	imports: [
		BrowserModule,
		HttpClientModule,
		AppRoutingModule,
		FormsModule
	],
	exports: [
	],
	providers: [],
	bootstrap: [ AppComponent ]
})
export class AppModule { }
