import 'package:flutter/material.dart';

class Movement {
  final String direction;
  final String speed;

  Movement({@required this.direction, this.speed});

  Movement.fromJson(Map<String, dynamic> json)
      : direction = json['direction'],
        speed = json['speed'];

  Map<String, dynamic> toJson() =>
    {
      'direction': direction,
      'speed': speed,
    };
}