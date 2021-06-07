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
let bonus = (x: int): (module BONUS with type t = int) =>
  (module
   {
     type t = int;
     let value = x;
   });

let bonus_2: module BONUS with type t = int =
  (module
   {
     type t = int;
     let value = 2;
   });
let default_bonus: module BONUS with type t = int =
  (module
   {
     type t = int;
     let value = 0;
   });

let get_bonus = b => {
  module M = (val b: BONUS with type t = int);
  M.value;
};
module Race = (B: BONUS with type t = int) : PLAYABLE => {
  type t = {
    name: string,
    abilities: Abilities.t,
  };
  let name = character => character.name;
  let make = name => {name, abilities: Abilities.init()};
  let constitution_bonus = B.value; /* here we get the value from module B */
  let constitution = character =>
    character.abilities.constitution + constitution_bonus;
};

module Dwarf = Race((val bonus(2)));
module Elf = Race((val bonus(0)));
module Tiefling = Race((val default_bonus));
//   without our bonus function
module Halfling =
  Race({
    type t = int;
    let value = 0;
  });
module HalfOrc = Race((val bonus(1)));
