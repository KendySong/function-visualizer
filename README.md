# function-visualizer
2 variables function interpreter and visualizer. $f(x, y) = z$

## Building
```git
- git clone https://github.com/KendySong/function-visualizer.git
- cd function-visualizer
- premake5 vs2022
```

## Examples
$$z = {(x^2 + y^2) \over 20} $$
```git
(x^2 + y^2)/20
```
<img src="https://github.com/KendySong/function-visualizer/blob/main/screenshots/0.png">

$$z = { x^2 \over 25 } - { y^2\over 25 } $$
```git
(x^2/25) - (y^2/25)
```
<img src="https://github.com/KendySong/function-visualizer/blob/main/screenshots/1.png">

$$z = {1-abs(x + y) - abs(y-x)}$$
```git
(x^2/25) - (y^2/25)
```
<img src="https://github.com/KendySong/function-visualizer/blob/main/screenshots/2.png">

$$z = {cos(abs(x)+abs(y))}$$
```git
cos(abs(x)+abs(y))
```
<img src="https://github.com/KendySong/function-visualizer/blob/main/screenshots/3.png">

## Interpreter features
- Pi
- Euler constant
- cos
- sin
- tan
- acos
- asin
- atan
- sqrt
- log
- ln
- abs
