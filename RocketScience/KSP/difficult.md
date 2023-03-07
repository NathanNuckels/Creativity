# All the stuff I struggle with.

# Rondevous
I spelled that wrong. Definitly.

'Rondevous' means getting near another craft, 'docking' is actually connecting the two together.

If you're going to 'rondevous' your probibly going to 'dock' as well.

The only thing you can do without docking is transfer kerbals and science.


C1 and C2 are in circular orbits. C1 is lower than C2. How can C1 rondevous with C2?
Obviously you make a manuver burning prograde until the orbits intersect but how do you know
where to put the burn?

T = orbital period P = Phase time p = phase angle O = number of orbits needed to sync

P = T \* (p/360)

T = 2π \* sqrt(a<sup>3</sup>/GM)

T<sub>trans</sub> = T<sub>current</sub> + P<sub>current</sub> / O

a<sub>trans</sub> = cuberoot((sqrt(a<sub>now</sub><sup>3</sup>/GM)+P/o)<sup>2</sup>GM )

Its hard to write out this monster in markdown so
paste this into desmos to soo what the equation REALLY looks like.

`a_{trans}=\sqrt[3]{\left(\sqrt{a_{current}^{3}/GM}+P/o\right)^{2}GM}`

And now the delta V:

V<sub>node</sub> = sqrt( GM((2/r<sub>node</sub>) - (1/a<sub>now</sub>)) ) - sqrt( GM((2/r<sub>node</sub>) - (1/a<sub>trans</sub>)) ) )

`V_{node}=\sqrt{GM\left(\frac{2}{r_{node}}-\frac{1}{a_{now}}\right)}-\sqrt{GM\left(\frac{2}{r_{node}}-\frac{1}{a_{trans}}\right)}`

And finally, the mega equation:

V<sub>node</sub> = sqrt( GM((2/r<sub>node</sub>) - (1/a<sub>now</sub>)) ) - sqrt( GM((2/r<sub>node</sub>) - (1/cuberoot((sqrt(a<sub>now</sub><sup>3</sup>/GM)+P/o)<sup>2</sup>GM )) ) )

`V_{node}=\sqrt{GM\left(\frac{2}{r_{node}}-\frac{1}{a_{now}}\right)}-\sqrt{GM\left(\frac{2}{r_{node}}-\frac{1}{\sqrt[3]{\left(\sqrt{a_{current}^{3}/GM}+P/o\right)^{2}GM}}\right)}`

EDIT: Simplified version!

`\sqrt{u\left(\frac{2}{r}-\frac{1}{\sqrt[3]{\frac{u\left(2\pi\sqrt{\frac{a^{3}}{u}}+\frac{2\pi\sqrt{\frac{a^{3}}{u}}\left(p/360\right)}{o}\right)^{2}}{4\pi^{2}}}}\right)}-\sqrt{2\pi\left(\frac{2}{r}-\frac{1}{a}\right)}`
