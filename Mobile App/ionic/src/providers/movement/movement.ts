import { Injectable } from '@angular/core';
import { HttpClient } from '@angular/common/http';

@Injectable()
export class MovementProvider {
  URL: string = 'http://192.168.4.1/move';

  constructor(public http:  HttpClient) {
  }

  postForward() {   
    let direction = {
      "direction": "FORWARD",
      "speed": 150
    }

    this.postMovements(direction);
  }

  postReverse() {   
    let direction = {
      "direction": "REVERSE",
      "speed": 150
    }

    this.postMovements(direction);
  }

  postLeft() {   
    let direction = {
      "direction": "LEFT",
      "speed": 150
    }

    this.postMovements(direction);
  }

  postRight() {   
    let direction = {
      "direction": "RIGHT",
      "speed": 150
    }

    this.postMovements(direction);
  }

  postStop() {   
    let direction = {
      "direction": "STOP",
    }

    this.postMovements(direction);
  }

  postMovements(direction)
  {
    this.http.post('http://192.168.4.1/move', direction, )
      .subscribe(msg => {
        console.log(msg);
       }, error => {
        console.log(error);
      });
  }

}
