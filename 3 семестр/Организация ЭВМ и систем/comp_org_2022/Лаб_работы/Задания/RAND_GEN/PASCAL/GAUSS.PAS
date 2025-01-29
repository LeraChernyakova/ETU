  procedure Gauss(Si:real;var R1,R2:real);
    var A,R,P:real;
    begin
      R:=sqrt(ln(1.0/sqr(random)));
      A:=2.0*Pi*random;
      R1:=R*cos(A)*Si;
      R2:=R*sin(A)*Si;
    end;
