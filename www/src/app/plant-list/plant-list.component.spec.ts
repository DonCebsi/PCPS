import { async, ComponentFixture, TestBed } from '@angular/core/testing';

import { PlantListComponent } from './plant-list.component';
import { mockPlantPrev1, mockPlantPrevs } from '../PlantPrev.mockdata';


import { of } from 'rxjs/observable/of';

describe('PlantListComponent', () => {
  let component: PlantListComponent;
  let fixture: ComponentFixture<PlantListComponent>;

  beforeEach(async(() => {
    TestBed.configureTestingModule({
      declarations: [ PlantListComponent ]
    })
    .compileComponents();
  }));

  beforeEach(() => {
    fixture = TestBed.createComponent(PlantListComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
  
  it('should get list of plants', fakeAsync(() => {
	const spy = spyOn(component, 'plants').and.returnValue(Observable.of(mockPlantPrev1);
	component.ngOnInit();
	expect(component.plants).toBe([ mockPlantPrev1 ]);
  });
  
  it('should clear list of plants', fakeAsync(() => {
	const spy = spyOn(component, 'plants').and.returnValue(Observable.of(mockPlantPrev1);
	component.ngOnInit();
	expect(component.plants).toBe([ mockPlantPrev1 ]);
	component.ngOnDestroy();
	expect(component.plants).toBe([]);
  });
  
});
