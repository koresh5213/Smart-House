Brief README file. For full information please contact me at kor5213@gmail.com

Usage
Compile: make Executer
Run: Executer <config-file>

About
This is a smart house system. All system components are called 'Agents', and we can add as many as we like dynamically.
Agent's behaviour is dictaed by .SO pre-compiled file placed in 'Agents' folder.

Agents
Agents that sends messages called 'Sensor', and agents that recieves messages is called 'Controller'.
An agents must inherit its class.
Agent CAN be both a sensor and a controller, but then it must be a virtual inheritance.

Config file
For every agent we will have those properties:

[ AC-163 ] -> agent id (must be unique)
type = ambient_temp ->type name, must match function TypeName()
room = room6A -> Room id
floor = 6 -> Floor number
log = AC -> Signature for log file usage
config = units: F; lower: 55; upper: 155; period: 2.3 -> Free string to be used by the agent

Contact 
Please feel free to contanct me at kor5213@gmail.com
