// Generated by ReScript, PLEASE EDIT WITH CARE
'use strict';


function to_string(dwarf) {
  return dwarf.name;
}

function of_string(name) {
  return {
          name: name
        };
}

var Dwarf = {
  to_string: to_string,
  of_string: of_string
};

function to_string$1(elf) {
  return elf;
}

function of_string$1(name) {
  return name;
}

var Elf = {
  to_string: to_string$1,
  of_string: of_string$1
};

var gimly = {
  name: "Gimly"
};

console.log("Gimly");

exports.Dwarf = Dwarf;
exports.Elf = Elf;
exports.gimly = gimly;
/*  Not a pure module */
