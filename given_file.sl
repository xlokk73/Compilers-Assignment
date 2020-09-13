ff Square(x:float) : float { return x*x;
}
ff XGreaterThanY(x:float , y:float) : auto { var ans : bool = true ;
if (y > x) { ans = false; } return ans ;
}
ff AverageOfThree(x:float , y:float , z:float) : float { var total:float = x + y + z;
return total / 3;
}
var x: float = 2.4;
var y:auto = Square(2.5);
print y;
print XGreaterThanY(x, 2.3);
print XGreaterThanY(Square(1.5) , y); print AverageOfThree(x, y, 1.2);
//6.25 //true //false //3.28
