# Custom Pillows Quest
This mod is a port of the custom pillows mod by the same name for pc, made by Toni Macaroni, [find their repo here](https://github.com/ToniMacaroni/CustomPillows)

## How to add custom textures

Custom Textures are put in the images folder at `/sdcard/ModData/com.beatgames.beatsaber/Mods/CustomPillowsQuest`, this means that a possible file path for a texture might be `/sdcard/ModData/com.beatgames.beatsaber/Mods/CustomPillowsQuest/images/example.png`

Custom textures tend to have to be 1:2 aspect ratio. The textures included with the mod are 474x1012 pixels, but other sizes should work as well. The image type shouldn't matter either, but make sure that you are actually putting images in the images folder. Most commonly images will be .jpg or .png

## How to add custom constellations

Custom constellations are put in the constellations folder at `/sdcard/ModData/com.beatgames.beatsaber/Mods/CustomPillowsQuest`, this means that a possible file path for a constellation might be `/sdcard/ModData/com.beatgames.beatsaber/Mods/CustomPillowsQuest/constellations/example.json`

### Making custom constellations
The constellation files are json files, and provide you with the ability to position & rotate the pre made piles in the menu. there are currently 6 types of pile to choose from, which is selected by putting any of these numbers into the "type" field in the "piles" array in the json file:
 - 0: Single
 - 1: Double Flat
 - 2: Double
 - 3: Triple
 - 4: Large Pile
 - 5: Arch

Examples of these piles are in the following image:

![piles](https://raw.githubusercontent.com/RedBrumbler/CustomPillowsQuest/master/ExtraFiles/Piles.png)

Then you can change the position by changing the "pos" x, y and z values.
You can also change the rotation by changing the "rot" x, y and z values. For those familiar with unity: these are the euler angles, not a quaternion

An example of a valid json that spawns 1 pillow right in front of the player is as follows:
```
{
  "constellationName": "single",
  "pillows": [
    {
      "type": 0,
      "pos": {
        "X": 0.0,
        "Y": 0.0,
        "Z": 2.0
      },
      "rot": {
        "X": 0.0,
        "Y": 0.0,
        "Z": 0.0
      }
    }
  ]
}
```

## Credits

* [zoller27osu](https://github.com/zoller27osu), [Sc2ad](https://github.com/Sc2ad) and [jakibaki](https://github.com/jakibaki) - [beatsaber-hook](https://github.com/sc2ad/beatsaber-hook)
* [darknight1050](https://github.com/darknight1050), [Futuremapopermydud](https://github.com/Futuremappermydud), [Sc2ad](https://github.com/sc2ad) - [questui](https://github.com/darknight1050/questui)
* [Sc2ad](https://github.com/sc2ad)  - [bs utils](https://github.com/sc2ad/QuestBS-Utils)
* [Sc2ad](https://github.com/sc2ad)  - [codegen](https://github.com/sc2ad/BeatSaber-Quest-Codegen)
* [Sc2ad](https://github.com/sc2ad)  - [custom types](https://github.com/sc2ad/Il2CppQuestTypePatching)
* [ToniMacaroni](https://github.com/ToniMacaroni) - [Original Idea](https://github.com/ToniMacaroni/CustomPillows)
