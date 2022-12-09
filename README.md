# OOPs Projects and Notes

### Non-linear differential equation solver

Given a Non-Linear differential Equation of the form: 
A * d^2u/dx^2 + B * d^2u/dy^2 + C * du/dx + D * du/dy + E =0

where A,B,C,D,E are functions of x,y, and u on [a,b] x [c,d]

with boundary conditions

u(a,y) = f1(y), u(b,y) = f2(y)
u(x,c) = g1(x), u(x,d) = g2(x).

<img width="823" alt="Screenshot 2022-12-09 at 8 53 55 PM" src="https://user-images.githubusercontent.com/52539396/206736513-6c42a3db-9949-446f-9adc-65feb9396dfd.png">

Using main.cpp we generate the .csv files and then using Plotter.m in MATLAB we plot the solution to the given differential eqn.

Sample soln:

![qn2](https://user-images.githubusercontent.com/52539396/206736705-c246b083-03eb-446a-9c0f-31e4edc70800.png)


## Weather App (App1)

One can pass the latitude and longitude coordinates of a location and the program "antipode_2.py" generates a marker on the location which gives the weather update of the required location.

In this app we created a new class in "geopoint.py" file and it inherits Weather from sunny day library and also made use of the Map from folium library in python.

<img width="911" alt="Screenshot 2022-12-09 at 11 55 32 PM" src="https://user-images.githubusercontent.com/52539396/206768607-7b29fadd-ee15-4fd7-8df2-3d620bca2b25.png">
