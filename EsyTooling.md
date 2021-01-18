#Tooling #ReasonML

ReasonML natif dispose d'un outillage exceptionnel, grâce à l'ecosystème OCaml. Dans ce billet, je vous propose de créer depuis 0 un projet ReasonML natif. Nous parcourerons l'outillage de gestion de dépendance, de construction logicielle, de travail dans un bac à sable par projet.

    Ce billet est le troisième de la série d'articles ReasonML : la série

Tirer le fil du destin
Take it Esy

Nous allons créer un projet nommé sorte (il s'agit du nom de la magie divinatoire pratiquée par les Strega de Vodacce).

Nous allons utiliser esy.sh, pour l'installer avec npm npm i -g esy.

Esy est une toolchain pour ReasonML et OCaml, inspirée du workflow de npm, et basée sur Opam et Dune dont nous parlerons ensuite.

Esy présente plusieurs intérêt :

    Un CLI unique pour plusieurs outils
    Le sandboxing des dépendances au niveau du projet
    Le fait de pouvoir coupler des dépenses issues de OPAM, NPM, GIT, REASON-NATIVE
    La simplification de la configuration Dune

Initialisation

Dans notre répertoire projet, nous commençons par créer les fichiers nécessaire :
```bash
touch sorte; cd sorte
echo '(lang dune 2.8)\n (name sorte)' >> dune-project
echo '(dirs (:standard \ node_modules \ _esy))' >> dune
touch package.json
touch sorte.opam
```
    Le fichier dune-project se place à la racine du projet et sert à définir les informations communes, à minima la version de Dune utilisée.

    Au moment où j'écris ce billet, j'utilise la version 1.11, bien que la dernière version soit la 2.4 en raison de limite de esy avec la version 2

    Le fichier dune se place à la racine et dans chaque répertoire qui correspond à une unité de compilation, c'est à dire une librairie ou un exécutable.
    Le fichier package.json est le manifeste du projet esy.
    Le fichier sorte.opam défini une librairie opam.

Gestion des dépendances

Commençons par éditer une première version du manifeste package.json :
```json
{
  "name": "sorte",
  "version": "0.0.1",
  "description": "Sorte is a 7th characters builder written in ReasonML",
  "license": "MPL-2.0",
  "scripts": {
    "pesy": "bash -c 'env PESY_MODE=update pesy'",
    "start": "esy x SorteApp.exe",
    "test": "esy x TestSorte.exe"
  },
  "dependencies": {
    "@opam/dune": ">=1.11",
    "@esy-ocaml/reason": "*",
    "ocaml": "~4.8.1000"
  },
  "devDependencies": {
    "ocaml": "~4.8.1000",
    "refmterr": "*",
    "pesy": "*",
    "@opam/merlin": "*",
    "@reason-native/rely": "*"
  },
  "esy": {
    "build": "dune build -p <PACKAGE_NAME>",
    "buildDev": "pesy",
    "release": {
      "releasedBinaries": ["SorteApp.exe"]
    }
  },
  "buildDirs": {
    "lib": {
      "namespace": "Lib",
      "name": "sorte.lib",
      "require": []
    },
    "bin": {
      "main": "SorteApp",
      "name": "SorteApp.exe",
      "require": ["sorte.lib"]
    },
    "test": {
      "namespace": "Test",
      "name": "sorte.test",
      "ocamloptFlags": ["-linkall", "-g"],
      "require": ["sorte.lib", "rely.lib"]
    },
    "test-runner": {
      "main": "TestSorte",
      "name": "TestSorte.exe",
      "require": ["sorte.test"]
    }
  }
}
```
Comme vous le constatez, ce fichier mime le package.json de npmjs avec quelques spécificités propres à esy.
# Scripts

Les scripts fonctionnent comme pour npm, à la différence qu'ils se lancent avec la commande esy [NOM_DU_SCRIPT].

Pour installer les dépendances, il suffit d'exécuter la commande esy install. C'est là que Esy commmence à montrer son intérêt : à la différence de NPM, les dépendances sont installées dans votre $HOME/.esy et linkées dans le répertoire node_modules de votre projet. C'est à dire que, d'une part, elles sont sandboxées pour votre projet, et d'autre part, qu'elles ne sont installées qu'une seule fois pour tous les projets utilisant la même version de la dépendance : une sacrée optimisation pour votre disque dur.
# Dependencies

Vous constatez que certaines dépendances sont préfixées par un namespace :

    @opam/ : signifie que la librairie sur cherchée sur opam, par exemple @opam/dune
    @reason-native/ : signifie que la librairie sur cherchée dans le projet reason-native.com , par exemple @reason-native/rely

Il est également possible d'avoir des résolutions sur npm, préfixées par @npm/, utiles pour les projet js_of_ocaml ou depuis n'importe quelle origine en utilisant des resolutions

Vous pouvez mainteant exécuter le commande :

```bash
esy install
```
# Ajouter des dépendances

Il est bien sûr possible d'ajouter les dépendences directement en utilisant le CLI. Dans le cas de ce projet je souhaite utliser Irmin dont je parlerai prochainement.

```bash
esy add @opam/irmin @opam/irmin-unix @opam/irmin-git
```

# Génération de configuration

Je vous propose une arborescence assez classique :
```sh
        |- bin #contient l'executable principal de notre projet
        |- lib #contient le métier de notre projet
        |- test #contient les tests de notre lib
        |_ test-runner #contient l'execution de nos tests
```
Vous pouvez mainteant exécuter le commande suivante, qui correspond au script de votre manifeste :
```bash
> esy pesy
```
N'hésitez pas à consulter les fichiers Dune générer dans chaque répertoire, pour appréhender cet outtil.

    Si vous êtes déjà familier de Dune, vous remarquerez que l'attribut name correspond à l'attribut public_name de Dune alors que l'attribut namespace correspond à l'attribut name de Dune

Vous pouvez ensuite compiler et executer le programme issu de cette génération.

```bash
    esy build # compile le projet
    esy x SorteApp.exe # exécute l'exécutable
```

ou le script que nous avons déclaré dans notre manifeste

```bash
    esy start
```
Vous venez de réalisez votre premier Hello world en initialisant votre projet.

Bien que beaucoup de configurations soient disponibles via pesy, vous pouvez rencontrer des limitations. Dans ce cas, il vous suffit de supprimer le noeud buildDirs de votre manifeste et de continuer à gérer manuellement vos fichiers Dune.

Pesy permet également de démarrer un projet à partir d'un template, vous pouvez utiliser le mien :
```bash
pesy --template=github:oteku/reason-native-template
```
