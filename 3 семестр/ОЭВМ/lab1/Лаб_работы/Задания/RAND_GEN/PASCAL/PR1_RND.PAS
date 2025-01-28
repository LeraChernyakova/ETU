program prov_rnd;
    const  n = 20;
    var  i,j    : integer;
         rnd_arr: array [1..n] of integer;
         rez    : text;
      begin
        assign(rez,'r.txt');
        rewrite(rez);
        randomize;
            writeln;
        write(rez, 'Рез-ты генерации пслуч. чисел');
            writeln(rez);
          for j:= 1 to 20 do
          begin
          for i:= 1 to n do
            begin
              rnd_arr[i] := random(100);
              write (rez,'ra[',i:2,']=',rnd_arr[i]);
              writeln(rez);
            end;
          writeln(rez);
          end;
          close(rez)
       end.