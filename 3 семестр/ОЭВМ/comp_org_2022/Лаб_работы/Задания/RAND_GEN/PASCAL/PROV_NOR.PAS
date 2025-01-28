program prov_nor;
    const  n = 5;
    var  i      : integer;
         s,r1,r2: real;
         rnd_arr: array [1..n] of real;
    procedure Gauss(Si:real;var R1,R2:real);
    var A,R,P:real;
    begin
      R:=sqrt(ln(1.0/sqr(random)));
      A:=2.0*Pi*random;
      R1:=R*cos(A)*Si;
      R2:=R*sin(A)*Si;
    end;
      begin
        randomize;
        writeln;
        write('input s:');
        readln(s);
        writeln;
        write('Рез-ты генерации пслуч. чисел');
            writeln;
          for i:= 1 to n do
            begin
              gauss(s, r1,r2);
              rnd_arr[i] := r1;
              write ('ra[',i:2,']=',rnd_arr[i]);
              writeln;
            end;
       end.