You'll need Orbiter 2016, D3D9Client, and Microsoft DirectX June 2010

I recommend XRSound2.0, and the XR fleet.

Also I found a Soyuz addon.

Anso see SpaceX-2015-2019 mission pack, but bewhere! You'll need to install
about 30 other mods to make it work and you'll probibly need an Orbiter Fourm
account to get some of them. Falcon9, FalconHeavy, BetterSpaceStation, Falcon9block4,
There's a lot of stuff.

If sound dosn't work, install XRSoundBridge (todo: get link)

First, creaet an orbiter folder. you'll want a folder for your wineprefix, and
a folder for orbiter itself. You'll also need a temperary folder for directx.

```sh
mkdir orbiter
cd orbiter
```

```sh
mkdir orbiter2016 wine directx
```

Now you'll need to install wine and winetricks if you havn't already.

```sh
Debian/Ubuntu/Pop_OS...
sudo apt install wine winetricks

Arch/Artix/Manjaro/Arch Craft...
# Edit your pacman.conf file.
# Look for multilib stuff and uncomment it
sudo pacman -Sy wine winetricks
```

Now you need to create the wine prefix and open its settings

```sh
#Replace ~/orbiter/wine with your wine prefix dir
WINEARCH=win32 WINEPREFIX=~/orbiter/wine winecfg
```

Change the supported windows version to Windows 8.1 and close it.

Now you'll need to install some packages... A lot of them.

C++ 2005, 2008, 2010, 2012, 2013, and 2015. DirectX 9, fonts, and other stuff.

```sh
#All the GUI installers
WINEPREFIX=~/orbiter/wine winetricks vcrun{2005,2008,2010,2012,2013,2015}

#The non-GUI installers
WINEPREFIX=~/orbiter/wine winetricks vcrun6 vcrun6sp6 directx9 d3dx9

#Fonts. This might take a while
WINEPREFIX=~/orbiter/wine winetricks corefonts
```

Now, run the directx extract in the wine prefix.

```sh
WINEPREFIX=~/orbiter/wine wine directx-jun-2010.exe

#The Z: drive is the host machine. Extract it there for convienence.
# If you use my directory layout, it would be in
# Z:\home\<USERNAME>\orbiter\directx
```

Now run the extracted file

```sh
WINEPREFIX=~/orbiter/wine wine directx/DXSETUP.exe
```

Now you're ready to install orbiter and all of its stuff.

I recomend using a file explorer, even a tui file explorer like midnight commander
just so that you know exacticly what's going on.

You want to extract orbiter, and all of your mods on top of your orbiter
installation. If it asks you to override a file, always say yes. Keep the zip files
aarround as a backup, Particularly D3D9Client because its website has been taken
down and Orbiter2016 itself due to its filesize.

Lets run orbiter and see if everything works.

```sh
WINEPREFIX=~/orbiter/wine wine 2016/orbiter.exe
#Note: This is teh DirectX7 version of orbiter.
#Note: it might be 'Orbiter.exe'. I don't remember :(
```
Now the command to run orbiter from wine while setting the correct wineprefix is a bit
long so lets put it in a bsh file for convienence.

```sh
echo "WINEPREFIX=~/orbiter/wine wine 2016/Orbiter.exe">orbiter.sh
echo "WINEPREFIX=~/orbiter/wine wine 2016/Orbiter_ng.exe">orbiter_ng.sh
#Note: It might be 'orbiter' instead of 'Orbiter'. Please double check.
chmod +x orbiter.sh orbiter_ng.sh
```

Now you're all set. Try `./orbiter.sh` and see what happens.

Go to Modules and make sure to enable D3D9Client and all your other mods.

If your scenarios arnt showing up, this is fixed by cd-ing into your orbiter install
and then running it. You can make the bash file do this for you as well:

```sh
pushd ~/orbiter/2016
WINEPREFIX=~/orbiter/wine wine orbiter_ng.exe
popd
```

'pushd' will cd into orbiter and 'popd' will return you to where ever you were before
running the script. Convienient, eh?

Oh yeah, one final note. It shouldn't be neccesary to make multiple wine prefixes.
Since Orbiter is so non-invasive, you can have multiple isntallations of orbiter and
they won't mess with eachother.

As a final note, a project I've wanted to do would be to make a Orbiter Launcher that
handles all this for you but 'tis long off. I like C and hate Java but the final product
will probibly be made in python so taht I can get the UI looking how I want it.
Don't expectt anything good to come out of this. I don't do hobby projects, only wishful
thinking, but I will at least start it and try to make it easy to maintain so if I give up,
hopefully someone else will revive it...? Ok, we all know that'll never happen...
