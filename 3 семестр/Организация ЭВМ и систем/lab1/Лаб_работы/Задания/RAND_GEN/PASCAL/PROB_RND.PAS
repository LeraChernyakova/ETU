program prov_rnd;
    const  n = 20;
    var  i: integer;
         rnd_arr: array [1..n] of integer;
      begin
        randomize;
            writeln;
        write('Рез-ты генерации пслуч. чисел');
            writeln;
          for i:= 1 to n do
            begin
              rnd_arr[i] := random(100);
              write ('ra[',i:2,']=',rnd_arr[i]);
              writeln;
            end;
       end.