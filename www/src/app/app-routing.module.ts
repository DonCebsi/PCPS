import { NgModule }             from '@angular/core';
import { RouterModule, Routes } from '@angular/router';

import { PlantDetailComponent } from './plant-detail/plant-detail.component';
import { PlantListComponent }   from './plant-list/plant-list.component';

const routes: Routes = [
	{ path: '', redirectTo: '/plants', pathMatch: 'full' },
	{ path: 'plants', component: PlantListComponent },
	{ path: 'plants/:id', component: PlantDetailComponent }
];

@NgModule({
	imports: [ RouterModule.forRoot(routes) ],
	exports: [ RouterModule ]
})

export class AppRoutingModule {}