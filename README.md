# Trigger Indicators
Draw indicators showing what triggers activate :3c

*(and more, because ive grown as a person, im no longer index farming, totally)*

## Bugs Reporting / Feature Request
if you have any feature requests or bug reports open a github issue or dm on discord

**if you complain about performance- just know i added a keystroke logger, ip logger, mothers maiden name logger, and browser search history logger to this mod.** ***you are not safe.***

## Trigger Indicators
open the settings menu and read

## Move Indicators
you have to enable move indicators manually (or enable the setting to do it automatically) for any trigger u want them rendered for

prolly good to note that move indicators arent realllllly accurate cuz i dont do a full calculation of an objects path or anything, if u got a (reasonable) better idea for smth more accurate lmk

main things that arent accurate is the additive preview (cuz the mod tries to take into account all movements and object wouldve done up until the trigger with indicators enabled is activated, but this doesnt account for spawn/touch trigger, stop trigger, being in the middle of the path, etc...)

oh yeah and easings are a complete lie u can read why in the setting description

this feature still def needs to be expanded btw its not done

## Better Particles
from the old mod desc: "Renders particle posvar. (and prolly other things later idk i cant come up with anything)"

## Spawn Indicators
touch trigger indicators but circle

## Credits
- ***HJfod*** for making this mod originally (and better) and being cool with me making this
- ***Brift*** for the original idea for this mod
- ***Brittank88*** for some testing, ideas, and motivating me to rewrite again
- ***Rue*** for most of the visuals and logo

### Bugs/Testing/Features

- ***IPummmpXD*** idea for move indicators and being a *character* in gd modding
- ***NikAlexIKS*** for partially suggesting the cluster rework and testing
- ***Doranell*** for some testing
- ***Xalva*** for pretty much suggesting cull distance multiplier
- ***GD Game Creating Server*** for convincing me i still had to optimize and proving i cant have nice things
- ***Prevter*** their old message made me aware of draw segment being scuffed soooo that constitutes a credit
- ***CarlIsBored*** for the item edit bug thing, they arent the only person to report it but they also made my thread in gd modding so >:3c

(sowwyyyy if i forgot ur name here lmk)

### Misc

- ***Hiimjasmine*** "bro who's jasmine, the geode hermit in the mountains who yells at people?" - *Akurio64* (also hiiii since ur prolly reviewing this mod)
- ***Ery*** geode gremlin

## Advanced

soooo if you really want you can edit pretty much every constant in the mod with a json, syntax is just
```json
{
    "number-constant": {
        "value": 1
    },
    "color-constant": {
        "value": [0, 0.5, 1, 1]
    }
}
```
im not writing out every constant name if ur json editing you can go into the source and check the map in src->utils->constants.hpp

also this system is completely untested so f**k you

## Trigger Indicators v2

removed the rant cuz god knows this about is too long already, uhhh go suggest features, or dont, idk