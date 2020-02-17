import 'package:flutter/material.dart';
import 'package:app/models/movement.dart';
import 'package:http/http.dart';

final String FORWARD = 'FORWARD';
final String REVERSE = 'REVERSE';
final String LEFT = 'LEFT';
final String RIGHT = 'RIGHT';
final String STOP = 'STOP';

void main() => runApp(MyApp());

class MyApp extends StatelessWidget {
  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      title: 'Flutter Demo',
      debugShowCheckedModeBanner: false,
      theme: ThemeData(
        primarySwatch: Colors.blue,
      ),
      home: MyHomePage(title: 'Remote Falcon'),
    );
  }
}

class MyHomePage extends StatefulWidget {
  MyHomePage({Key key, this.title}) : super(key: key);

  final String title;

  @override
  _MyHomePageState createState() => _MyHomePageState();
}

class _MyHomePageState extends State<MyHomePage> {

  void _makePostRequest(Movement movement) async {
    String url = 'http://192.168.4.1:80/move';
    Map<String, String> headers = {"Content-type": "application/json"};
    String json = movement.toJson().toString();

    // await post(url, headers: headers, body: json);
    Response response = await post(url, headers: headers, body: json);
    //int statusCode = response.statusCode;
    //return response.body;
    print(response.statusCode);
    print(response.body);
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: Text(widget.title),
      ),
      body: Center(
        child: Column(
          crossAxisAlignment: CrossAxisAlignment.center,
          mainAxisAlignment: MainAxisAlignment.center,
          children: <Widget>[
            Button(
              child: Icon(Icons.arrow_upward, color: Colors.white,),
              onTapUp: (TapUpDetails details) {
                _makePostRequest(Movement(direction: STOP));
              },
              onTapDown: (TapDownDetails details) {
                _makePostRequest(Movement(direction: FORWARD));
              },
            ),
            Row(
              mainAxisAlignment: MainAxisAlignment.center,
              crossAxisAlignment: CrossAxisAlignment.center,
              children: <Widget>[
                Button(
                  child: RotatedBox(quarterTurns: 135, child: Icon(Icons.arrow_upward, color: Colors.white,)),
                  onTapUp: (TapUpDetails details) {
                    _makePostRequest(Movement(direction: STOP));
                  },
                  onTapDown: (TapDownDetails details) {
                    _makePostRequest(Movement(direction: LEFT));
                  },
                ),
                SizedBox(width: 100,),
                Button(
                  child: RotatedBox(quarterTurns: 45, child: Icon(Icons.arrow_upward, color: Colors.white,)),
                  onTapUp: (TapUpDetails details) {
                  _makePostRequest(Movement(direction: STOP));
                },
                onTapDown: (TapDownDetails details) {
                  _makePostRequest(Movement(direction: RIGHT));
                },
                ),
              ],
            ),
            Button(
              child: RotatedBox(quarterTurns: 90, child: Icon(Icons.arrow_upward, color: Colors.white,)),
              onTapUp: (TapUpDetails details) {
                _makePostRequest(Movement(direction: STOP));
              },
              onTapDown: (TapDownDetails details) {
                _makePostRequest(Movement(direction: REVERSE));
              },
            ),
          ],
        ),
      ),
    );
  }
}

class Button extends StatelessWidget {
  Button({@required this.child, this.onTapUp, this.onTapDown});
  
  final Widget child;
  final GestureTapUpCallback onTapUp;
  final GestureTapDownCallback onTapDown;

  @override
  Widget build(BuildContext context) {
    return GestureDetector(
      onTap: () {},
      onTapDown: onTapDown,
      onTapUp: onTapUp,
      child: Container(
        height: 100,
        width: 100,
        color: Colors.blue,
        child: Center(child: child),
      ),
    );
  }
}
