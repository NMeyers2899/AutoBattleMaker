# Introduction
This is a modular aggro system. Meant for use in games that have enemies that target other characters.
# How to Use
Unit Characters are a type of character that on their own have a potential list of targets. And they use a behavior tree that 
cycles through allowing them to act if they are close enough to a target, chase if they are too far from their target, or patrol
if they have no target. As a developer you are meant to easily add on to the unit's stats. Determine how they increase or decrease 
the priority of their potential targets. And what happens when they act.
# Known Bugs
Removing units from the list of potential targets is tricky. Make sure that if units can be removed from a list that those updates 
occur before the first task node is referenced.
