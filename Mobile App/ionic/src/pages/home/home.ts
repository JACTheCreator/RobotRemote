import { Component } from '@angular/core';
import { NavController } from 'ionic-angular';
import { MovementProvider } from '../../providers/movement/movement';

@Component({
  selector: 'page-home',
  templateUrl: 'home.html',
})
export class HomePage {

  constructor(public navCtrl: NavController, public movementProvider: MovementProvider) {

  }

  moveForward(event) {
    console.log("moveForward");
    this.movementProvider.postReverse();
  }

  moveBack(event) {
    console.log("moveBack");
    this.movementProvider.postForward();
  }

  moveLeft(event) {
    console.log("moveLeft");
    this.movementProvider.postLeft();
  }

  moveRight(event) {
    console.log("moveRight");
    this.movementProvider.postRight();
  }

  moveStop(event) {
    console.log("moveStop");
    this.movementProvider.postStop();
  }
}
