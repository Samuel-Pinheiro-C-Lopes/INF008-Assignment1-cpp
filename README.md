# INF008 T1 Samuel Pinheiro Coutinho Lopes

First assignment from OOP subject ministered by Sandro Andrade, made by the undergraduate student Samuel Pinheiro Coutinho Lopes in C++ and CMake.


## Setup

To build the project navigate through the CLI to the root where the CMakeList.txt is located and run the following command:

```bash
mkdir build && cd build && cmake ..
```

This will create a build folder within the root directory, move towards it and then run cmake for the project.

cmake will, besides generate a make setup for you, also install the library and handle linkage configuration, assuring it will be installed and linked to the project.

After this, the build directory must've been filled with cache, build outputs and cmake files. To compile the project and execute it right away:

```bash
make && ./ASSGN_1
```
You must receive a prompt from the project by now.


## Usage
The project has a main menu with four options:
- 1 Register potential participants to the university; 
- 2 Print different data about the university; 
- 3 Register participant(s) to events; and
- 4 Generate a log file with the university data.  

The three first options will redirect the user to specific menus where more precise selections can be done, while the fourth one tries to create and write a [university.json] file with the current data present in the university - that's thanks to the **nlohmann_json** library used for this project.
Credits and more informations: <https://github.com/nlohmann/json>.

### Registrations
When registering an event or participant you may need to take care with the input provided since both CPF and Date fields are validated internally - to ease the process of registering new participants, I suggest generating valid cpfs with online tools like: <https://www.invertexto.com/gerador-de-cpf>.


## Internal Structure

### Alias
In the include directory there is a alias folder that holds a header file with a defined namespace with some types definitions with the usual "using [alias] = [type]" notation.

Said that, you may notice that most occurrences, if not all, of *std::unordered_map<T, G>* where exchanged for a simple *Map<T, G>* definition - there aren't other types of maps there, so I didn't thought I needed to be more specific. The same occurred with the *std::shared_ptr<T>* that was exchanged for *Ptr<T>* - once more, it is not specifying the type of pointer because during the project development no *std::raw_ptr* or *std::unique_ptr* were used. The same can be said about the *std::vector<T>*, exchanged for Vector<T>.

Those chooses were made as attempts to increase maintenance and readability. 

### Entity
The core class of the project, it declares *virtual* *void printSelf()*, *int nextId()* and *Json serializeSelf()* methods - virtual used here to allow them to be abstract methods and also be override in the future. It also declares a *const int Id* data member and the *int getId()* public method.

The class defines that a concrete implementation of it must have a way of getting the next id, print and serialize itself, and also is identificable through a numeric field and, since the protected constructor needs a int id, it also demands that the identity field is obtained during it construction.

*printSelf()* and *serializeSelf()* are meant to be override in each inheritage from this in a transitive demeanor, always complementing the methods with new data present in the new classes while still using the just override method as base for it.

That actually settles most of the logic put toward the serialization and user interaction through OOP modeling: every entity that inherits from Entity will use the ascendant classes methods to print and serialize, always adding to the override method the extended data it may have.

### Prompt
Most of the user input through the CLI were handled by the static *Prompt* class that encapsulated methods to handle the display of options, data, clearing invalid input, getting user input, selections and others.
It has a nested class *forType<T>* with prompt methods for polymorphic behavior through pointers or simply to handle objects overall.

The Prompt class methods are present in empty constructors from classes within this project with the purpose of filling them with user input whenever a new instance is created.

That was the best approach I could come with to maintain the assignment of the data outside the constructor's body for performance, not needing to write exhaustive code with forms for each type added and still being able to get data from the user.

It's also part of the logic put toward OOP modeling present in this project with the intent of diminishing repeated code and actually reuse some of the code already written for some classes - when a new class is created, it's just needed to pass how, through input, it will handle the new data members - the already present ones are being handled by the ascendant classes in their respective constructors. Of course, this doesn't limit the construction of the classes since constructor overloading is used to expose multiple ways to build a class. 

### Event<T>
The concrete classes that represent the available events for the manager inherit from the Event abstract class with a specific template that tells which kind of attendee are expected. 
type *T* must inherit from Participant, so a *static_assert* with the *std::is_base_of* from *<type_traits>* is made to make sure of it during compilation time.
The *Event<T>* class by itself inherit from a *BaseEvent* class that encapsulates a private date member, it's initialization and a date getter - that was needed to get latter, through dynamic linkage (late binding), the date from any type of event in the university.

### Participant
An abstract class from which all the concrete participants inherit. 

### Registration<T>
One of the tasks in hand was to support online and in person events with different behaviors for each of them - and thus, registrations classes that hold the participant with some data about it's registration and, through inheritance of OnlineEventRegistration and InPersonEventRegistration, different behavior in the registration - through their constructors to be more specific - was the approach chosen. Via polymorphism it was possible to handle different types of registration the same through the commom interface.

### CPF and Date
Both are object values with validation behavior encapsulated within. 
