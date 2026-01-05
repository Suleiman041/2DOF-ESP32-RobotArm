clc;clear;close all;

l1 = 7.7;
l2 = 8.5;

xstart = 0;
ystart = 16;

xend = 5;
yend = 11;

steps = 60;

figure;
axis equal;
xlim([-20 20]);
ylim([-20 20]);
xlabel('X'); ylabel('Y');
grid on;
hold on;

for i = 0:steps
    t = i/steps;
    
    %linear interpolation
    y = ystart + t*(yend-ystart);
    x = xstart + t*(xend-xstart);

    r = sqrt(x^2 + y^2);
    phi1 = acos((l1^2 + r^2 - l2^2)/(2*l1*r));
    phi2 = atan2(y, x);
    phi3 = acos((l1^2 + l2^2 -r^2)/(2*l1*l2));
    
    theta1 = phi2 + phi1;
    theta2 = -(pi - phi3);
    th1 = rad2deg(theta1);
    th2 = rad2deg(theta2);
    
    angle1 = mapservo(th1, -90,90,0,180);
    angle2 = mapservo(th2, -90,90,0,180);
    
    thetat1 = angle1 -90;
    thetat2 = angle2 - 90;
    
    thet1 = deg2rad(thetat1);
    thet2 = deg2rad(thetat2);
    
    x1 = l1*cos(thet1);
    x2 = l1*cos(thet1) + l2*cos(thet1+thet2);
    
    y1 = l1*sin(thet1);
    y2 = l1*sin(thet1) + l2*sin(thet1+thet2);
    

    cla

    plot([0,x1,x2],[0,y1,y2],'-o','LineWidth',1.5);
    drawnow
end

function output = mapservo(value,inmin,inmax,outmin, outmax)
    output = ((outmax-outmin)*(value-inmin)/(inmax-inmin)+outmin);

end