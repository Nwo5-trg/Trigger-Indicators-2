# Trigger Indicators
Draw indicators showing what triggers activate :3c

*(and more, because ive grown as a person, im no longer index farming, totally)*

## Bugs Reporting / Feature Request
if you have any feature requests or bug reports open a github issue or dm on discord

**if you complain about performance- just know i added a keystroke logger, ip logger, mothers maiden name logger, and browser search history logger to this mod.** ***you are not safe.***

## Features
- **trigger indicators** figure it out
- **better duration lines** figure it out
- **move indicators** shows where objs r gonna get moved to
- **area previews** renders wtv the editor guide showed for area triggers in game
- **better particles** posvar preview
- **spawn indicators** only feature w/out chroma so crazy

## Trigger Indicators
its in the name vro, theres a bunch of settings so go read

## Better Duration Lines
*completely ignores arrow triggers btw f\*\*\* that*

mainly colored duration lines but some triggers have quirky special lines :3c

- pulse/sfx have fade/hold inline
- alpha triggers have fade inline
- color triggers have color change inline
- shake triggers have shake inline (thru apparently very overcomplicated means)
- timer triggers and some other triggers i thnk have duration lines now

there r some other settings go read them

## Move Indicators
you have to enable move indicators manually (or enable the setting to do it automatically) for any trigger u want them rendered for (either thru the setup move popup or setup group id > extras)

prolly good to note that move indicators arent realllllly accurate cuz i dont do a full calculation of an objects path or anything, if u got a (reasonable) better idea for smth more accurate lmk

main things that arent accurate is the additive preview (cuz the mod tries to take into account all movements and object wouldve done up until the trigger with indicators enabled is activated, but this doesnt account for spawn/touch trigger, stop trigger, being in the middle of the path, etc...)

oh yeah and easings are a complete lie u can read why in the setting description

this feature still def needs to be expanded btw its not done

## Area Previews
enabled same way as move indicators but is on by default

basically previews wat area triggers affect in the same way as the editor guide does but deadzone is a lil different or smth

## Better Particles
from the old mod desc: "Renders particle posvar. (and prolly other things later idk i cant come up with anything)"

## Spawn Indicators
touch trigger indicators but circle

## Credits
- ***HJfod*** for making this mod originally (and better) and being cool with me making this (also for me just stealing all their stuff all the time)
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
- ***undefined*** half of the better duration lines previews r just stolen :3
- ***Alpha*** stole good grid code 4r better duration lines :3c

(sowwyyyy if i forgot ur name here lmk)

### Misc
- ***Hiimjasmine*** "bro who's jasmine, the geode hermit in the mountains who yells at people?" - *Akurio64* (also haiiii since ur prolly reviewing this mod)
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

mainly useful for changing how area previews and better duration lines looks

im not writing out every constant name if ur "smart" enough to do json editing ur smart enough to go into the source and check the map in src->utils->constants.hpp

also this system is completely untested so f\*\*\* you

## Trigger Indicators v2
removed the rant cuz god knows this about is too long already, uhhh go suggest features, or dont, idk