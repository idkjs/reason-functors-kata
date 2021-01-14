+++
title = "Reason : DnD Kata"
date = 2020-12-27
draft = false
[taxonomies]
tags = ["Reason"]
+++

Text translation

When I discover or want to explain a concept, I quite like to rely on a Kata, a short exercise to highlight a programming practice. I therefore suggest the ** DnD Kata **, whose objective is to model a team of characters for part of the Dungeons and Dragons role-playing game. Of course, modeling the set of rules is a complex exercise, we will content ourselves here with representing a character by:

-   her name
-   his race
-   his skills, including of course his racial bonuses

A team is a collection of characters, which can be of different races.

The educational objective of this kata is to illustrate [Reason functors] (https://oteku.github.io/reasonml-modules/#les-foncteurs) and to demonstrate how they contribute to applying the S.O.L.I.D principles in Reason.

## About Dungeons and Dragons

Dungeons & Dragons a.k.a DnD is a role-playing game where players take on the role of heroes in a fantasy universe. The main universe of this game is Faerûn, a continent of the planet Abeir-Toril. We will be using the [Dungeons & Dragons 5th Edition under the Open-Gaming (OGL) license] system (https://github.com/Umbyology/OGL-SRD5).

## We are the Dwarves

We'll start by modeling the Dwarves, one of Faerûn's playable races, by name.

We already know that a good way to have a namespace in Reason is to use namespaces, so we can start with this representation:

```reason
module Dwarf = {
  type t = string;
};

```

In this implementation, the type of the module is inferred. You can also make it explicit by adding a module signature and modeling the Elves at the same time:

```reason
// module signature
module Dwarf: {type t = string;} = {
  type t = string;
};
// module signature used to model elves
module Elf: {type t = string;} = {
  type t = string;
};
```

At this step we notice that the 2 modules share the same signature. Since the Elf and Dwarf modules represent playable heroes, this seems legitimate and we will clarify that all playable heroes share the same signature. To do this, we can use one type of module:

```reason
module type PLAYABLE = {type t = string;};

module Dwarf: PLAYABLE = {
  type t = string;
};

module Elf: PLAYABLE = {
  type t = string;
};

```

The other modules don't need to know the form of type `PLAYABLE.t`, they just need to know that it exists and the module must expose functions to be able to be used.

We call this an ** abstraction **, because we make the type `t` abstract:

```reason

module type PLAYABLE = {
    type t;
    let to_string: t => string;
    let of_string: string => t;
};

```

Each PLAYABLE type module must implement these functions. Let's do it:

```reason
module Dwarf: PLAYABLE = {
  type t = {name: string};
  let to_string = (dwarf) => dwarf.name;
  let of_string = (name) => {name: name};
};

module Elf: PLAYABLE = {
  type t = string;
  let to_string = (elf) => elf;
  let of_string = (name) => name;
};
```

Since `t` is abstract, you will notice that each module implementing` PLAYABLE` can have a different concrete type for `t`. This is perfectly fine as long as they stick to their module type contract.

From another module, we cannot access a concrete value of `t`, but we can create a Dwarf or get a representation as a` string`.

```reason
let gimly = Dwarf.of_string("Gimly");

let () = Dwarf.to_string(gimly) |> print_endline;
```

## Heroes have characteristics

In DnD, a hero is also represented by his characteristics:

-   Strength represents physical power, natural athletic ability
-   Dexterity represents agility, reflexes, balance
-   The Constitution represents health, endurance, vital force
-   Intelligence represents mental acuity, reasoning, memory
-   Wisdom represents perception, intuition, insight
-   Charisma represents strength of personality, eloquence, leadership

There are several optional rules for characteristics at creation, we will only implement those for _Standard scores_. At the start, each ability has a value of 10:

```reason
module Abilities = {
  type t = {
    strength: int,
    dexterity: int,
    constitution: int,
    intelligence: int,
    wisdom: int,
    charisma: int
  };
  let init = () => {
    strength: 10,
    dexterity: 10,
    constitution: 10,
    intelligence: 10,
    wisdom: 10,
    charisma: 10
  };
};

```

We can thus develop our `Dwarf` module:

```reason
module Dwarf: PLAYABLE = {
  type t = {
    name: string,
    abilities: Abilities.t
  };
  let to_string = (dwarf) => dwarf.name;
  let of_string = (name) => {name, abilities: Abilities.init()};
};
```

The names of our functions are no longer very appropriate, so we are going to update the `PLAYABLE` module type then the` Elf` and `Dwarf` modules:

```reason
module type PLAYABLE = {
    type t;
    let name: t => string;
    let make: string => t;
};

module Dwarf: PLAYABLE = {
  type t = {
    name: string,
    abilities: Abilities.t
  };
  let name = (dwarf) => dwarf.name;
  let make = (name) => {name, abilities: Abilities.init()};
};

module Elf: PLAYABLE = {
  type t = {
    name: string,
    abilities: Abilities.t
  };
  let name = (elf) => elf.name;
  let make = (name) => {name, abilities: Abilities.init()};
};
```

## Races give modifiers

### Dwarves have a +2 constitution bonus

In Reason, mods are top notch, which means you can use a mod as values. We can therefore create a new type of module to represent a bonus and functions to represent a bonus of 2:

```reason
module type BONUS = {
    type t;
    let value: t;
};
```

As well as a value which makes it possible to obtain a module of this type:

```reason
let bonus_2: (module BONUS with type t = int) =
  (module
   {
     type t = int;
     let value = 2;
   });
```

`bonus_2` is a modulus as a value. Since `t` is abstract, we need to add a witness type` with type t = int`.

To extract the value of the bonus, we also need a getter:

```reason
let get_bonus = (b) => {
  module M = (val (b: (module BONUS with type t = int)));
  M.value;
};
```

> I admit that the syntax of the first order modules is not the most pleasant, we will see that their use is after all limited. If you are looking for additional explanations you can read: https://dev.realworldocaml.org/first-class-modules.html

We can now write:

```reason
module Dwarf: PLAYABLE = {
  type t = {
    name: string,
    abilities: Abilities.t
  };
  let name = (dwarf) => dwarf.name;
  let make = (name) => {name, abilities: Abilities.init()};
  let constitution = (dwarf) => dwarf.abilities.constitution + get_bonus(bonus_2);
};

```

### Let's not forget the Elves, Half-Orcs, Halflings or Tieflings

The Dwarves are not the only race of Faerûn. Each has a different constitution bonus. Half-Orcs have +1 while Elves, Halflings, and Tieflings have no constitution bonus.

When the data of a function varies, we add a function parameter to avoid code duplication. We can do the same at the module level. Reason has ** functors ** which are functional modules: module (s) to module functions.

We can therefore create a `Race` functor:

```reason
module Race = (B: BONUS with type t = int) : PLAYABLE => {
  type t = {
    name: string,
    abilities: Abilities.t
  };
  let name = (character) => character.name;
  let make = (name) => {name, abilities: Abilities.init()};
  let constitution_bonus = B.value; /* here we get the value from module B */
  let constitution = (character) => character.abilities.constitution + constitution_bonus;
};

```

> Reads: the `Race` functor takes as parameter a` B` module of type `BONUS` whose type` t` is `int` and returns a module of type` PLAYABLE`.

Then we can easily build our modules:

```reason
// we add a function to manage all bonus
let bonus = (x: int) : (module BONUS with type t = int) =>
  (module
   {
     type t = int;
     let value = x;
   });

```reason

//  we use our Race functor to create the five races
module Dwarf =
  Race(val bonus(2));
module Elf =
  Race(val bonus(0));
module Tiefling =
  Race(val default_bonus);
//   without our bonus function
module Halfling =
  Race({
    type t = int;
    let value = 0;
  });
module HalfOrc =
  Race(val bonus(1));
```

> You now understand why we introduced the top notch modules previously. They facilitate the passage of value between the _ Type level _ and the _ Module level _, which is very practical here.

### All skills can have bonuses

Functors are not limited to one parameter, so we can use the same trick for all characteristics:

```reason
module Race =
       (
         BS: BONUS with type t = int,
         BD: BONUS with type t = int,
         BC: BONUS with type t = int,
         BI: BONUS with type t = int,
         BW: BONUS with type t = int,
         BCh: BONUS with type t = int
       )
       : PLAYABLE => {
  type t = {
    name: string,
    abilities: Abilities.t
  };
  let name = (character) => character.name;
  let make = (name) => {name, abilities: Abilities.init()};
  let bonus =
    Abilities.{
      strength: BS.value,
      dexterity: BD.value,
      constitution: BC.value,
      intelligence: BI.value,
      wisdom: BW.value,
      charisma: BCh.value
    };
  let abilities = (character) =>
    Abilities.{
      strength: character.abilities.strength + bonus.strength,
      dexterity: character.abilities.dexterity + bonus.dexterity,
      constitution: character.abilities.constitution + bonus.constitution,
      intelligence: character.abilities.intelligence + bonus.intelligence,
      wisdom: character.abilities.wisdom + bonus.wisdom,
      charisma: character.abilities.charisma + bonus.charisma
    };
};

module Dwarf =
  Race(
    (val bonus(0)),
    (val bonus(0)),
    (val bonus(2)),
    (val bonus(0)),
    (val bonus(0)),
    (val bonus(0))
  );
```

For our use case, this is not practical, we need to remember the order of bonuses. We already have a type that represents all the `Abilities.t` capacity values, let's use it:

```reason
//  just create a bonus function that take a Abilities.t and return a Bonus module
let bonus = (x: Abilities.t) : (module BONUS with type t = Abilities.t) =>
  (module
   {
     type t = Abilities.t;
     let value = x;
   });


// the functor `Race` take a module` B` of type `BONUS` whom type` t` is `Abilities.t`
// ** as parameter and then return a module of type `PLAYBLE`
module Race = (B: BONUS with type t = Abilities.t) : PLAYABLE => {
  type t = {
    name: string,
    abilities: Abilities.t
  };
  let name = (character) => character.name;
  let make = (name) => {name, abilities: Abilities.init()};
  let bonus =
    Abilities.{
      strength: B.value.strength,
      dexterity: B.value.dexterity,
      constitution: B.value.constitution,
      intelligence: B.value.intelligence,
      wisdom: B.value.wisdom,
      charisma: B.value.charisma
    };
  let abilities = (character) =>
    Abilities.{
      strength: character.abilities.strength + bonus.strength,
      dexterity: character.abilities.dexterity + bonus.dexterity,
      constitution: character.abilities.constitution + bonus.constitution,
      intelligence: character.abilities.intelligence + bonus.intelligence,
      wisdom: character.abilities.wisdom + bonus.wisdom,
      charisma: character.abilities.charisma + bonus.charisma
    };
};

// (* create our Dwarf module *)
Dwarf module = Race (val bonus Abilities. {
    strength = 0
  ; dexterity = 0
  ; constitution = 2
  ; intelligence = 0
  ; wisdom = 0
  ; charisma = 0
  })
```

To be more concise and explicit, we can work from a `no_bonus` value:

```reason
let no_bonus =
  Abilities.{strength: 0, dexterity: 0, constitution: 0, intelligence: 0, wisdom: 0, charisma: 0};

module Dwarf = Race((val bonus(Abilities.{...no_bonus, constitution: 2})));
module Elf = Race((val bonus(Abilities.{...no_bonus, dexterity: 2})));
module Halfling = Race((val bonus(Abilities.{...no_bonus, dexterity: 2})));
module Tiefling =
  Race((val bonus(Abilities.{...no_bonus, charisma: 2, intelligence: 1})));
module HalfOrc = Race((val bonus(Abilities.{...no_bonus, strength: 2})));
```

### Summary

By the end of this section, you should have:

```reason
module type PLAYABLE = {
  type t;
  let name: t => string;
  let make: string => t;
};
module Abilities = {
  type t = {
    strength: int,
    dexterity: int,
    constitution: int,
    intelligence: int,
    wisdom: int,
    charisma: int,
  };
  let init = () => {
    strength: 10,
    dexterity: 10,
    constitution: 10,
    intelligence: 10,
    wisdom: 10,
    charisma: 10,
  };
};
module DwarfImpl: PLAYABLE = {
  type t = {
    name: string,
    abilities: Abilities.t,
  };
  let name = dwarf => dwarf.name;
  let make = name => {name, abilities: Abilities.init()};
};
module ElfImpl: PLAYABLE = {
  type t = {
    name: string,
    abilities: Abilities.t,
  };
  let name = elf => elf.name;
  let make = name => {name, abilities: Abilities.init()};
};
module type BONUS = {
  type t;
  let value: t;
};
let get_bonus = b => {
  module M = (val b: BONUS with type t = int);
  M.value;
};
let bonus = (x: Abilities.t): (module BONUS with type t = Abilities.t) =>
  (module
   {
     type t = Abilities.t;
     let value = x;
   });
module Race = (B: BONUS with type t = Abilities.t) : PLAYABLE => {
  type t = {
    name: string,
    abilities: Abilities.t,
  };
  let name = character => character.name;
  let make = name => {name, abilities: Abilities.init()};
  let bonus =
    Abilities.{
      strength: B.value.strength,
      dexterity: B.value.dexterity,
      constitution: B.value.constitution,
      intelligence: B.value.intelligence,
      wisdom: B.value.wisdom,
      charisma: B.value.charisma,
    };
  let abilities = character =>
    Abilities.{
      strength: character.abilities.strength + bonus.strength,
      dexterity: character.abilities.dexterity + bonus.dexterity,
      constitution: character.abilities.constitution + bonus.constitution,
      intelligence: character.abilities.intelligence + bonus.intelligence,
      wisdom: character.abilities.wisdom + bonus.wisdom,
      charisma: character.abilities.charisma + bonus.charisma,
    };
};
module Dwarf =
  Race(
    (
      val bonus(
            Abilities.{
              strength: 0,
              dexterity: 0,
              constitution: 2,
              intelligence: 0,
              wisdom: 0,
              charisma: 0,
            },
          )
    ),
  );
let no_bonus =
  Abilities.{
    strength: 0,
    dexterity: 0,
    constitution: 0,
    intelligence: 0,
    wisdom: 0,
    charisma: 0,
  };
module Dwarf = Race((val bonus(Abilities.{...no_bonus, constitution: 2})));
module Elf = Race((val bonus(Abilities.{...no_bonus, dexterity: 2})));
module Halfling = Race((val bonus(Abilities.{...no_bonus, dexterity: 2})));
module Tiefling =
  Race((val bonus(Abilities.{...no_bonus, charisma: 2, intelligence: 1})));
module HalfOrc = Race((val bonus(Abilities.{...no_bonus, strength: 2})));
```
You can easily add any race, for example humans have +1 to all characteristics:

```reason
module Human =
  Race(
    (
      val bonus(
            Abilities.{
              strength: 1,
              dexterity: 1,
              constitution: 1,
              intelligence: 1,
              wisdom: 1,
              charisma: 1,
            },
          )
    ),
  );
```
## United color of Faerûn

Each player can play a character of a different race. How to model a team?

### The companions of the Hall

> The companions is a book by R.A. Salvatore a novelist who wrote many short stories located in Faerûn

Let's start by creating the characters, we already have everything we need:

```reason
let catti = Human.make("Catti-brie");

let regis = Halfling.make("Regis");

let bruenor = Dwarf.make("Bruenor Battlehammer");

let wulfgar = Human.make("Wulfgar");

let drizzt = Elf.make("Drizzt Do'Urden");
```

We can create value for our teammates:

```reason
❌ let companions = [catti, regis, bruenor, wulfgar, drizzt];
```

** Error: This expression has type Halfing.t but an expression was expected of type
Human.t **

Remember that the type of `list` is`type t('a) = list('a);`, the inference engine has `'a = Human.t` because it is the type of the first element of our list`catti`, but the` regis` type is `Halfing.t`.

How could we help the compiler? Type parameters must be concrete types.

```reason
(* won't compile PLAYABLE is a module type *)
❌ type team = list(PLAYABLE.t);

(* won't compile RACE is a functor
** aka a function from module to module *)
❌ type team = list(RACE.t);
```

In reality, there is nothing too complicated, the main point is that the Reason lists are monomorphic, so we need a unique type that can represent a character, whatever their race:

```reason
type buddy =
  | Dwarf(Dwarf.t)
  | Elf(Elf.t)
  | Halfing(Halfling.t)
  | Tiefling(Tiefling.t)
  | HalfOrc(HalfOrc.t)
  | Human(Human.t);

let companions = [Human(catti), Halfing(regis), Dwarf(bruenor), Human(wulfgar), Elf(drizzt)];
```

However, there are many other races in Faerûn, as well as variants. Drizzt for example is actually a dark elf and not an elf. It would be more appropriate to use [polymorphic variants] (https://dev.realworldocaml.org/variants.html#scrollNav-4) in order to facilitate the extension of our library, because we are still in the embryo of a real character generator:

```ocaml
let companions_final =
    [`Human catti; `Halfing regis; `Dwarf bruenor; `Human wulfgar; `Elf drizzt]
```
```reason
let companions_final = [
  `Human(catti),
  `Halfing(regis),
  `Dwarf(bruenor),
  `Human(wulfgar),
  `Elf(drizzt)
];
```

whose type will be

```reason
let companions_final:
  list([> `Dwarf(Dwarf.t)
        | `Elf(Elf.t)
        | `Halfing(Halfling.t)
        | `Human(Human.t) ]) =
  [`Human(<abstr>), `Halfing(<abstr>), `Dwarf(<abstr>), `Human(<abstr>),
   `Elf(<abstr>)];
```

## Take away

1. Reason provides useful abstractions for:

-   namespace: ** module **
-   protocol: ** module type **
-   extension: ** functor **
-   default value or implementation: ** functor ** or ** first-class module **
    -   functors are module (s) to module functions
    -   first order modules are values ​​and allow communication between type level and module level.

2. S.O.L.I.D is not only a good OOP practice:

-   Single responsibility principle => module
-   Open / closed principle => module
-   Liskov substitution principle => module type
-   Interface segregation principle => module type
-   Dependency inversion principle => functor
