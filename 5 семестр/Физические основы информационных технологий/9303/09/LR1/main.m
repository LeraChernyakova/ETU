function main
  D = 0.8*2;    # redacted
  L = 18;
  a = 40;
  function retval = get_n(y)
    retval = 1.4+0.12*cos(3*y);
  endfunction
  N = 10^4;   # accuracy
  
####################
  dy = (D/2)/N; # dy = const
  y0 = 0;       # current point (z, y)
  z0 = 0;
  
  dS_array = [];
  z_array = [z0];
  y_array = [y0];
  
  z = [];       # graphic points (z, y)
  y = [];
  
  S = 0;        # ray path length
#################### 
  a = a*(pi/180);
  a_i = a; # angle
  n_i = 0;          # current n
  n_i_next = 0;     # temp value
  dS_i = 0;         # current dS
  dz_i = 0;         # current dz
  for i = 1:N
    n_i = get_n(y0);
    
    dS_i = dy / sin(a_i);
    dz_i = dy / tan(a_i);
    
    dS_array = [dS_array, dS_i];
    
    y0 += dy;
    z0 += dz_i;
    y_array = [y_array, y0];
    z_array = [z_array, z0];
    
    n_i_next = get_n(y0);
    a_i = get_a(a_i, n_i, n_i_next);
    n_i = n_i_next;
  endfor

  # sum of quarters
  k = floor(L/z0);  # number of quarters of period
  for i = 1:k
    switch(mod(i, 4))
      case 1
        z = [z, z_array.+((i-1)*z0)];
        y = [y, y_array];
      case 2
        z = [z, z0.-fliplr(z_array).+((i-1)*z0)];
        y = [y, fliplr(y_array)];
      case 3
        z = [z, z_array.+((i-1)*z0)];
        y = [y, y_array.*-1];
      case 0
        z = [z, z0.-fliplr(z_array).+((i-1)*z0)];
        y = [y, fliplr(y_array.*-1)];
    endswitch
  endfor
  
  # discrete sum in period
  S += sum(dS_array)*k;
  switch(mod(k+1, 4))
    case 2
      dS_array = fliplr(dS_array);
      z_array = z0.-fliplr(z_array);
      y_array = fliplr(y_array);
    case 3
      y_array = y_array.*-1;
    case 0
      dS_array = fliplr(dS_array);
      z_array = z0.-fliplr(z_array);
      y_array = fliplr(y_array.*-1);
  endswitch
  
  index = find(z_array<(L-z(end)))+1;
  z_array = z_array(1:index);
  y_array = y_array(1:index);
  dS_array = dS_array(1:index-1);
  
  # last point triangle calculation
  y_array(end) = y_array(end-1) + (y_array(end)-y_array(end-1))/(z_array(end)-z_array(end-1))*(L-z(end)-z_array(end-1));
  z_array(end) = L-z(end);
  dS_array(end) =  abs(dS_array(end)*(y_array(end)-y_array(end-1))/dy);
  z = [z, z_array.+(k*z0)];
  y = [y, y_array];
  S += sum(dS_array);
  
  image = plot(z, y, "r");
  hold on;
  grid on;
  xlabel('z');
  ylabel('y');
  xlim([0, L]);
  ylim([-D/2, D/2]);
  saveas(image, "graphics.png");
  
  filename = "results.txt";
  fid = fopen(filename, "w");
  fputs(fid, num2str(S, "%.6f"));
  fclose(fid);
endfunction

function retval = get_a(a, n1, n2)  # здесь косинус, потому что
  retval = acos(cos(a)*n1/n2);      # исходные данные соответствуют
endfunction                         # углу преломления = 90-a
