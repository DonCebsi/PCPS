import { async, ComponentFixture, TestBed } from '@angular/core/testing';

import { PlantDetailComponent } from './plant-detail.component';
import { mockPlant1, mockPlant2, mockPlants } from '../PlantDetail.mockdata';

import { of } from 'rxjs/observable/of';

describe('PlantDetailComponent', () => {
  let component: PlantDetailComponent;
  let fixture: ComponentFixture<PlantDetailComponent>;

  beforeEach(async(() => {
    TestBed.configureTestingModule({
      declarations: [ PlantDetailComponent ]
    })
    .compileComponents();
  }));

  beforeEach(() => {
    fixture = TestBed.createComponent(PlantDetailComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
  
  it('should have an h2 tag of plant id', () => {
	expect(de.query(By.css('h2')).nativeElement.innerText).toBe('Plant {{this.id}}');
  });
  
  it('should return the right color value', () => {
	expect(component.colorHash("key")).toBe("rgb(74,251,164)");
  });
  
  it('should get right plant id of plant 1', fakeAsync(() => {
	const spy = spyOn(component, 'plant').and.returnValue(Observable.of(mockPlant1);
	component.ngOnInit();
	expect(component.plant.id).toBe(1);
  });
  
  it('should get right plant size of plant 2', fakeAsync(() => {
	const spy = spyOn(component, 'plant').and.returnValue(Observable.of(mockPlant2);
	component.ngOnInit();
	expect(component.plant.size).toBe(1);
  });
  
  it('should create a chart', fakeAsync(() => {
	const spy = spyOn(component, 'plant').and.returnValue(Observable.of(mockPlant2);
	component.ngOnInit();
	expect(component.chart).toBeTruthy();
  });
  
  it('should destroy chart from plant 1', fakeAsync(() => {
	const spy = spyOn(component, 'plant').and.returnValue(Observable.of(mockPlant1);
	component.ngOnInit();
	expect(component.chart).toBeTruthy();
	component.ngOnDestroy();
	expect(component.chart).toBeFalsy();
  });
  
  
  it('should destroy chart from plant 2', fakeAsync(() => {
	const spy = spyOn(component, 'plant').and.returnValue(Observable.of(mockPlant2);
	component.ngOnInit();
	expect(component.chart).toBeTruthy();
	component.ngOnDestroy();
	expect(component.chart).toBeFalsy();
  });
  
});
