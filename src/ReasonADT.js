// Generated by ReScript, PLEASE EDIT WITH CARE
'use strict';


function init(param) {
  return {
          strength: 10,
          dexterity: 10,
          constitution: 10,
          intelligence: 10,
          wisdom: 10,
          charisma: 10
        };
}

var Abilities = {
  init: init
};

function name(dwarf) {
  return dwarf.name;
}

function make(name) {
  return {
          name: name,
          abilities: {
            strength: 10,
            dexterity: 10,
            constitution: 10,
            intelligence: 10,
            wisdom: 10,
            charisma: 10
          }
        };
}

var DwarfImpl = {
  name: name,
  make: make
};

function name$1(elf) {
  return elf.name;
}

function make$1(name) {
  return {
          name: name,
          abilities: {
            strength: 10,
            dexterity: 10,
            constitution: 10,
            intelligence: 10,
            wisdom: 10,
            charisma: 10
          }
        };
}

var ElfImpl = {
  name: name$1,
  make: make$1
};

function get_bonus(b) {
  return b.value;
}

function bonus(x) {
  return {
          value: x
        };
}

function Race(B) {
  var name = function (character) {
    return character.name;
  };
  var make = function (name) {
    return {
            name: name,
            abilities: {
              strength: 10,
              dexterity: 10,
              constitution: 10,
              intelligence: 10,
              wisdom: 10,
              charisma: 10
            }
          };
  };
  return {
          name: name,
          make: make
        };
}

function name$2(character) {
  return character.name;
}

function make$2(name) {
  return {
          name: name,
          abilities: {
            strength: 10,
            dexterity: 10,
            constitution: 10,
            intelligence: 10,
            wisdom: 10,
            charisma: 10
          }
        };
}

var Dwarf = {
  name: name$2,
  make: make$2
};

function name$3(character) {
  return character.name;
}

function make$3(name) {
  return {
          name: name,
          abilities: {
            strength: 10,
            dexterity: 10,
            constitution: 10,
            intelligence: 10,
            wisdom: 10,
            charisma: 10
          }
        };
}

var Elf = {
  name: name$3,
  make: make$3
};

function name$4(character) {
  return character.name;
}

function make$4(name) {
  return {
          name: name,
          abilities: {
            strength: 10,
            dexterity: 10,
            constitution: 10,
            intelligence: 10,
            wisdom: 10,
            charisma: 10
          }
        };
}

var Halfling = {
  name: name$4,
  make: make$4
};

function name$5(character) {
  return character.name;
}

function make$5(name) {
  return {
          name: name,
          abilities: {
            strength: 10,
            dexterity: 10,
            constitution: 10,
            intelligence: 10,
            wisdom: 10,
            charisma: 10
          }
        };
}

var Tiefling = {
  name: name$5,
  make: make$5
};

function name$6(character) {
  return character.name;
}

function make$6(name) {
  return {
          name: name,
          abilities: {
            strength: 10,
            dexterity: 10,
            constitution: 10,
            intelligence: 10,
            wisdom: 10,
            charisma: 10
          }
        };
}

var HalfOrc = {
  name: name$6,
  make: make$6
};

function name$7(character) {
  return character.name;
}

function make$7(name) {
  return {
          name: name,
          abilities: {
            strength: 10,
            dexterity: 10,
            constitution: 10,
            intelligence: 10,
            wisdom: 10,
            charisma: 10
          }
        };
}

var Human = {
  name: name$7,
  make: make$7
};

var catti_abilities = {
  strength: 10,
  dexterity: 10,
  constitution: 10,
  intelligence: 10,
  wisdom: 10,
  charisma: 10
};

var catti = {
  name: "Catti-brie",
  abilities: catti_abilities
};

var regis_abilities = {
  strength: 10,
  dexterity: 10,
  constitution: 10,
  intelligence: 10,
  wisdom: 10,
  charisma: 10
};

var regis = {
  name: "Regis",
  abilities: regis_abilities
};

var bruenor_abilities = {
  strength: 10,
  dexterity: 10,
  constitution: 10,
  intelligence: 10,
  wisdom: 10,
  charisma: 10
};

var bruenor = {
  name: "Bruenor Battlehammer",
  abilities: bruenor_abilities
};

var wulfgar_abilities = {
  strength: 10,
  dexterity: 10,
  constitution: 10,
  intelligence: 10,
  wisdom: 10,
  charisma: 10
};

var wulfgar = {
  name: "Wulfgar",
  abilities: wulfgar_abilities
};

var drizzt_abilities = {
  strength: 10,
  dexterity: 10,
  constitution: 10,
  intelligence: 10,
  wisdom: 10,
  charisma: 10
};

var drizzt = {
  name: "Drizzt Do'Urden",
  abilities: drizzt_abilities
};

var companions_0 = {
  TAG: /* Human */5,
  _0: catti
};

var companions_1 = {
  hd: {
    TAG: /* Halfing */2,
    _0: regis
  },
  tl: {
    hd: {
      TAG: /* Dwarf */0,
      _0: bruenor
    },
    tl: {
      hd: {
        TAG: /* Human */5,
        _0: wulfgar
      },
      tl: {
        hd: {
          TAG: /* Elf */1,
          _0: drizzt
        },
        tl: /* [] */0
      }
    }
  }
};

var companions = {
  hd: companions_0,
  tl: companions_1
};

var companions_final_0 = {
  NAME: "Human",
  VAL: catti
};

var companions_final_1 = {
  hd: {
    NAME: "Halfing",
    VAL: regis
  },
  tl: {
    hd: {
      NAME: "Dwarf",
      VAL: bruenor
    },
    tl: {
      hd: {
        NAME: "Human",
        VAL: wulfgar
      },
      tl: {
        hd: {
          NAME: "Elf",
          VAL: drizzt
        },
        tl: /* [] */0
      }
    }
  }
};

var companions_final = {
  hd: companions_final_0,
  tl: companions_final_1
};

var no_bonus = {
  strength: 0,
  dexterity: 0,
  constitution: 0,
  intelligence: 0,
  wisdom: 0,
  charisma: 0
};

exports.Abilities = Abilities;
exports.DwarfImpl = DwarfImpl;
exports.ElfImpl = ElfImpl;
exports.get_bonus = get_bonus;
exports.bonus = bonus;
exports.Race = Race;
exports.no_bonus = no_bonus;
exports.Dwarf = Dwarf;
exports.Elf = Elf;
exports.Halfling = Halfling;
exports.Tiefling = Tiefling;
exports.HalfOrc = HalfOrc;
exports.Human = Human;
exports.catti = catti;
exports.regis = regis;
exports.bruenor = bruenor;
exports.wulfgar = wulfgar;
exports.drizzt = drizzt;
exports.companions = companions;
exports.companions_final = companions_final;
/* No side effect */