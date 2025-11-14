## v0.1.0-beta.13

**Added**

- <cr>d</c><co>r</c><cy>a</c><cg>g</c> <cp>t</c><cr>r</c><co>i</c><cy>g</c><cg>g</c><cb>e</c><cp>r</c> <co>c</c><cy>o</c><cg>n</c><cb>n</c><cp>e</c><cr>c</c><co>t</c><cy>i</c><cg>o</c><cb>n</c><cp>s</c> :3c (enabled in settings)
- always draw extras setting for <cd>trigger indicator</c>
- dotted lines for <cd>trigger indicator</c>
- comments to constants
- rewrite extras for <cd>trigger indicator</c>
- changelog <cr>c</c><co>o</c><cy>l</c><cg>o</c><cb>r</c><cp>s</c> !
- rewrite draw circle cuz it was just disappearing sometimes so might as well :3

**Fixed**

- lowered <co>better duration lines</c> cull threshold
- something very dumb with drawing double lines when clustering
- very small and stupid bugs

## v0.1.0-beta.12
*(just adding wat ninkaz said p much)*

**Added**

- select only mode 4r <cr>area previews</c> and <cl>better particles</c>
- hide <co>duration lines</c> while playtesting
- better <cr>c</c><co>h</c><cy>r</c><cg>o</c><cb>m</c><cp>a</c> :333

**Removed**

- alpha fix cuz last update made that useless

**Fixed**

- layer alpha stuff
- color trigger inline previews

## v0.1.0-beta.11

**Added**

- rewrite draw line

**Fixed**

- line thickness being f\*\*cked
- triangles in transperant lines overlapping i think
- <cb>move indicator</c> culling

## v0.1.0-beta.10

**Added**

- <cr>b</c><co>e</c><cy>t</c><cg>t</c><cb>e</c><cp>r</c> <co>d</c><cy>u</c><cg>r</c><cb>a</c><cp>t</c><cr>i</c><co>o</c><cy>n</c> <cb>l</c><cp>i</c><cr>n</c><co>e</c><cy>s</c> <cb>&</c> <cr>a</c><co>r</c><cy>e</c><cg>a</c> <cp>p</c><cr>r</c><co>e</c><cy>v</c><cg>i</c><cb>e</c><cp>w</c><cr>s</c> !
- bugs prolly cuz i added 2 new features :3c

**Fixed**

- all of last update \<\/3
- culling kinda, moreso made it slightly better
- some tiny bugs

## v0.1.0-beta.9

**Added**

- a lil bit of code cleanup not rly

**Fixed**

- dont update stuff options
- exit static triggers
- supercede or however u spell it better particles

## v0.1.0-beta.8

**Added**

- <cb>move indicator</c> toggles to setup move popup
- made that a lil more clear in about
- <cp>f</c><cd>e</c><cf>mb</c><cd>o</c><cp>y</c> flag logo :3c

## v0.1.0-beta.7

**Added**

- <cr>f</c><co>u</c><cy>l</c><cg>l</c> <cp>r</c><cr>e</c><co>w</c><cy>r</c><cg>i</c><cb>t</c><cp>e</c> <co>2</c><cy>,</c> <cb>e</c><cp>l</c><cr>e</c><co>c</c><cy>t</c><cg>r</c><cb>i</c><cp>c</c> <co>b</c><cy>o</c><cg>o</c><cb>g</c><cp>a</c><cr>l</c><co>o</c><cy>o</c>
- reworked settings
- reworked clustering
- integrated <cl>better particles</c> into this mod :3c (better duration lines next update???)
- <cb>move indicators</c>
- constants customization cuz why not
- ***prolly*** runs better im not sure but like it should cuz i optimized it way more i think
- some more settings for <cd>trigger indicators</c>
- more credits :3
- new changelog formatting again :3c

**Fixed**

- maybe hopefully fixed stuff just not appearing on windows sometimes (please god)
- spawn indicators dont render if ur not on the objects layer
- a few visual bugs with extras i think
- some code ✨ *shenanigans* ✨

**Removed**

- collision ids mb
- group labels (these are not coming back btw)
- settings in readme, i trust you, please dont betray said trust, if i get ***one more f\*\*king bug report im going to commit a [serious crime]***

## v0.1.0-beta.6

**Added**

- spawn triggered indicators thickness
- collison id support :3333 (might be laggy ill make it better later)
- group labels (no group names support cuz it crashes for me but ill add it next update i can)
- some setting name changes
- cull distance multiplier
- new changelog formatting :3
- made code a lil more like better duration lines (cuz i think that mod was a lil cleaner)

**Fixed**

- flipping triggers breaking spawn indicators and extras
- item edit being scuffed

## v0.1.0-beta.5

**Added**

- soft toggles :3
- spawn triggered only
- spawn triggered indicators
- misc code cleanup
- updated about cuz go knows ppl dont check settings

**Fixed**

- center group indicators i think

## v0.1.0-beta.4

**Added**

- remembered using exists so cleaned up settings file (this does *not* deserve a version bump but wtv)

## v0.1.0-beta.3

**Added**

- alt textures for buttons (smth smth ery)

**Fixed**

- got rid of all globals i think (other than the namespace ones cuz obv i cant get rid of those)

## v0.1.0-beta.2

**Added**

- source
- settings button in editor
- trigger blacklist thing for triggers that dont work properly (might make toggleable later or smth but prolly not cuz the fixes would be annoying)
- group blacklist again
- organised files a lil bit
- node ids compat 3:

## v0.1.0-beta.1

**Added**

- seperate outputs for target and center
- rewrote ***the entire mod***
- 50 smth x performance boost or smth i aint even kidding
- new about
- like 3 geode versions bump
- some super serious settings

**Removed**

- dynamic updating we dont need that anymore
- adv rand and sequence trigger support, too much performance and rewriting for smth almost noone cares about
- group blacklist

**Fixed**

- a bunch of edge cases making indicators not update
- layer fade for extras
- all the code being in one file what was actually wrong with me

## v0.1.0-alpha.4

**Added**

- 2+ times performance boost somehow (prolly last big performance boost)
- clustering
- line cutting (thanks chatgpt)
- all selected objects draw all selected lines instead of just 1
- way more settings
- logo i forgot rue made sorry 😭

**Removed**

- updating when groups get added (ILL ADD IT BACK WHEN I FIGURE OUT HOW TRUST)

**Fixed**

- collision blocks are now treated as normal blocks but fr this time i think
- triggers updating more than they should

## v0.1.0-alpha.3

**Added**

- huge performance boost
- select object to see all incoming lines
- dynamic updating again
- settings reformat
- trigger only mode
- geode version bump

**Removed**

- updating every frame
- some types of groups being detected (temporarily)

**Fixed**

- group blacklist not working in the last release
- when selecting triggers line not appearing
- old code i forgot to delete

## v0.1.0-alpha.2

**Added**

- lines fading when on a different layer
- rewrote like all the indicator code (thanks**HJFod**)
- support for advanced random and sequence trigger

**Fixed**

- collision blocks are now treated as normal blocks
- input/output indicators now scale with the trigger
- change trail color when toggle trigger activated
- sometimes new triggers/blocks not updating

## v0.1.0-alpha.1

- First build