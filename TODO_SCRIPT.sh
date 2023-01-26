#Move some things between repos.
git clone https://github.com/NathanNuckels/TheTemperaryNotebook.git
git clone https://github.com/NathanNuckels/Creativity.git
cp -rv TheTemperaryNotebook/Stellius/scripts/ Creativity/Stellius/
cp -v TheTemperaryNotebook/Stellius/Hyperspace.txt Creativity/Stellius/wiki
cp -v TheTemperaryNotebook/Stellius/generic-place-names.csv Creativity/Stellius
cp -v TheTemperaryNotebook/Stellius/orbit-maker.txt
echo "Update hyperspace.txt">>Creativity/Stellius/TODO
echo "Update orbit-maker.txt">>Creativity/Stellius/TODO
echo "Add Planets: Mosphere, Percius, Stellius, XiraN, ">>Creativity/Stellius/TODO
cd Creativity
git add .
git status

#git commit -m "Moved things from other repo"
#git push origin master
#rm -rv TheTemperaryNotebook Creativity
