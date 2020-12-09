import { async, ComponentFixture, TestBed } from '@angular/core/testing';

import { PlantImportComponent } from './plant-import.component';

describe('PlantImportComponent', () => {
  let component: PlantImportComponent;
  let fixture: ComponentFixture<PlantImportComponent>;

  beforeEach(async(() => {
    TestBed.configureTestingModule({
      declarations: [ PlantImportComponent ]
    })
    .compileComponents();
  }));

  beforeEach(() => {
    fixture = TestBed.createComponent(PlantImportComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
