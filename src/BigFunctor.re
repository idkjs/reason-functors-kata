module type PLAYABLE = {
  type t;
  let name: t => string;
  let make: string => t;
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
module Race =
       (
         BS: BONUS with type t = int,
         BD: BONUS with type t = int,
         BC: BONUS with type t = int,
         BI: BONUS with type t = int,
         BW: BONUS with type t = int,
         BCh: BONUS with type t = int,
       )
       : PLAYABLE => {
  type t = {
    name: string,
    abilities: Abilities.t,
  };
  let name = character => character.name;
  let make = name => {name, abilities: Abilities.init()};
  let bonus =
    Abilities.{
      strength: BS.value,
      dexterity: BD.value,
      constitution: BC.value,
      intelligence: BI.value,
      wisdom: BW.value,
      charisma: BCh.value,
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
    (val bonus(0)),
    (val bonus(0)),
    (val bonus(2)),
    (val bonus(0)),
    (val bonus(0)),
    (val bonus(0)),
  );
