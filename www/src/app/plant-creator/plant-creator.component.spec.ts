import { async, ComponentFixture, TestBed } from '@angular/core/testing';

import { PlantCreatorComponent } from './plant-creator.component';

describe('PlantCreatorComponent', () => {
  let component: PlantCreatorComponent;
  let fixture: ComponentFixture<PlantCreatorComponent>;

  beforeEach(async(() => {
    TestBed.configureTestingModule({
      declarations: [ PlantCreatorComponent ]
    })
    .compileComponents();
  }));

  beforeEach(() => {
    fixture = TestBed.createComponent(PlantCreatorComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
  
  it('should submit template', () => {
	component.templateCreator = true;
    component.templateSubmit();
	expect(component.templateCreator).toBe(false);
  });
  
  it('should submit plant', () => {
    component.showDialog = true;
    component.document.getElementById('plant-name') = "Test";
    component.document.getElementById('plant-template') = "Template";
    component.nameInput.validity.valid = true;
    component.templateInput.validity.valid = true;
    component.plantSubmit();
    expect(component.showDialog).toBe(false);
  });
  
  it('should have an h3 tag of General', () => {
	expect(de.query(By.css('h3')).nativeElement.innerText).toBe('General');
  });
  
  it('should have an h3 tag of Temperature', () => {
	expect(de.query(By.css('h3')).nativeElement.innerText).toBe('Temperature');
  });
  
  it('should have an h3 tag of Moisture', () => {
	expect(de.query(By.css('h3')).nativeElement.innerText).toBe('Moisture');
  });
  
  it('should have an h3 tag of Humidity', () => {
	expect(de.query(By.css('h3')).nativeElement.innerText).toBe('Humidity');
  });
  
  it('should have an h3 tag of Light', () => {
	expect(de.query(By.css('h3')).nativeElement.innerText).toBe('Light');
  });
  
});
