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

// the functor `Race` take a module` B` of type `BONUS` whom type` t` is `Abilities.t`
// ** as parameter and then return a module of type `PLAYBLE`
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
// long version
// module Dwarf =
//   Race(
//     (
//       val bonus(
//             Abilities.{
//               strength: 0,
//               dexterity: 0,
//               constitution: 2,
//               intelligence: 0,
//               wisdom: 0,
//               charisma: 0,
//             },
//           )
//     ),
//   );


let no_bonus =
  Abilities.{strength: 0, dexterity: 0, constitution: 0, intelligence: 0, wisdom: 0, charisma: 0};

// using the no bonus function to spread in some default values
module Dwarf = Race((val bonus(Abilities.{...no_bonus, constitution: 2})));
module Elf = Race((val bonus(Abilities.{...no_bonus, dexterity: 2})));
module Halfling = Race((val bonus(Abilities.{...no_bonus, dexterity: 2})));
module Tiefling =
  Race((val bonus(Abilities.{...no_bonus, charisma: 2, intelligence: 1})));
module HalfOrc = Race((val bonus(Abilities.{...no_bonus, strength: 2})));

/* We can add new race with ease. Humans have +1 for all abilities */
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

let catti = Human.make("Catti-brie");

let regis = Halfling.make("Regis");

let bruenor = Dwarf.make("Bruenor Battlehammer");

let wulfgar = Human.make("Wulfgar");

let drizzt = Elf.make("Drizzt Do'Urden");

// let companions = [catti, regis, bruenor, wulfgar, drizzt];
let companions_final = [
  `Human(catti),
  `Halfing(regis),
  `Dwarf(bruenor),
  `Human(wulfgar),
  `Elf(drizzt)
];
