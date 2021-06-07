module type PLAYABLE = {
  type t;
  let to_string: t => string;
  let of_string: string => t;
};

module Dwarf: PLAYABLE = {
  type t = {name: string};
  let to_string = dwarf => dwarf.name;
  let of_string = name => {name: name};
};

module Elf: PLAYABLE = {
  type t = string;
  let to_string = elf => elf;
  let of_string = name => name;
};

let gimly = Dwarf.of_string("Gimly");

let () = Dwarf.to_string(gimly) |> print_endline;
