
Установка OpenCL-драйвера для процессора
========================================

Установить OpenCL-драйвер для процессора полезно, даже если у вас есть видеокарта, т.к. на нем удобно тестировать приложение (драйвер видеокарты гораздо чаще может повиснуть вместе с ОС).

Windows
-------
Скачайте [прямая ссылка для Windows](http://registrationcenter-download.intel.com/akdlm/irc_nas/vcp/13794/opencl_runtime_18.1_x64_setup.msi)
Установите

Linux (Рекомендуется Ubuntu 18.04 или 20.04)
----------------------------------

Скачайте [прямая ссылка для Ubuntu](http://registrationcenter-download.intel.com/akdlm/irc_nas/vcp/15532/l_opencl_p_18.1.0.015.tgz)
``apt-get install -yq cpio``
``tar -xzf l_opencl_p_18.1.0.015.tgz``
``sudo ./l_opencl_p_18.1.0.015/install.sh``
Проведите установку.

Если у вас довольно новый процессор, например i7-8550U, то драйвер может его не поддерживать - ```clCreateContext``` вернет ошибку ```CL_DEVICE_NOT_AVAILABLE```, в таком случае поставьте свежий драйвер [отсюда](https://github.com/intel/compute-runtime/releases) (включает в т.ч. драйвер для встроенной Intel GPU).


Установка OpenCL-драйвера для видеокарты
========================================

Windows
-------

Поставьте драйвер стандартным образом - скачав инсталлятор с официального сайта вендора вашей видеокарты и установив.

Linux
-----

NVidia: ``sudo apt install nvidia-384``

AMD: [скачав](https://www.amd.com/en/support) и установив amdgpu-pro драйвер

Проверка окружения (на примере Linux)
==============================================

 ``mkdir build``
 ``cd build``
 ``cmake ..``
 ``make -j4``
 ``./enumDevices`` должно увидеть хотя бы одну OpenCL-платформу:

```
Number of OpenCL platforms: 1
Platform #1/1
    Platform name: 
```

Если же вы видите ошибку:
``` 
terminate called after throwing an instance of 'std::runtime_error'
  what(): Can't init OpenCL driver!
Aborted (Core dumped)
```
То попробуйте установить ```sudo apt install ocl-icd-libopencl1``` и выполнить ``./enumDevices`` снова.

Если вы видите ошибку:
```
: CommandLine Error: Option 'polly' registered more than once!
LLVM ERROR: inconsistency in registered CommandLine options
```
То, наоборот, может помочь удалить пакет ```sudo apt remove ocl-icd-libopencl1``` и попробовать выполнить ``./enumDevices`` снова.

