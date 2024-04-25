import 'package:flutter/material.dart';

void main() {
  runApp(const MyApp());
}

class MyApp extends StatelessWidget {
  const MyApp({super.key});

  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      title: 'Boat App',
      debugShowCheckedModeBanner: false,
      theme: ThemeData(
        colorScheme: ColorScheme.fromSeed(seedColor: Colors.deepPurple),
        useMaterial3: true,
      ),
      home: const MyHomePage(title: 'Boat App'),
    );
  }
}

class MyHomePage extends StatefulWidget {
  const MyHomePage({super.key, required this.title});

  final String title;

  @override
  State<MyHomePage> createState() => _MyHomePageState();
}

class _MyHomePageState extends State<MyHomePage> {
  int _counter = 0;
  bool _engineStarted = false;

  String _statusMessage = 'To start the engine press boat button';

  bool _startEngine() {
    setState(() {
      _engineStarted = true;
      _statusMessage = 'Engine started successfully!';
    });
    return _engineStarted;
  }

  void _incrementCounter() {
    if (_engineStarted == true) {
      setState(() {
        _statusMessage = 'Boat started to move forward!';
        _counter++;
      });
    }
  }

  void _decrementCounter() {
    if (_engineStarted == true) {
      setState(() {
        _statusMessage = 'Engine started successfully!';
        _counter--;
      });
    }
  }

  void _stopEngine() {
    if (_engineStarted == true) {
      setState(() {
        _engineStarted = false;
        _statusMessage = 'Engine stopped successfully!';
        _counter = 0;
      });
    }
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        backgroundColor: Theme.of(context).colorScheme.inversePrimary,
        title: Align(
          alignment: Alignment.center,
          child: Text(widget.title),
        ),
      ),
      body: Center(
        child: Column(
          mainAxisAlignment: MainAxisAlignment.center,
          children: <Widget>[
            Text(
              _statusMessage,
            ),
            Text(
              'Speed $_counter km/h',
              style: Theme.of(context).textTheme.headlineMedium,
            ),
          ],
        ),
      ),
      floatingActionButton: Row(
        mainAxisAlignment: MainAxisAlignment.center,
        children: [
          FloatingActionButton(
            onPressed: _startEngine,
            tooltip: 'StartEngine',
            child: const Icon(IconData(0xe1d3, fontFamily: 'MaterialIcons')),
          ),
          const SizedBox(width: 16),
          FloatingActionButton(
            onPressed: _decrementCounter,
            tooltip: 'Decrement',
            child: const Icon(Icons.remove),
          ),
          const SizedBox(width: 16),
          FloatingActionButton(
            onPressed: _incrementCounter,
            tooltip: 'Increment',
            child: const Icon(Icons.add),
          ),
          const SizedBox(width: 16),
          FloatingActionButton(
            onPressed: _stopEngine,
            tooltip: 'StopEngine',
            child: const Icon(Icons.stop),
          ),
        ],
      ),
    );
  }
}
