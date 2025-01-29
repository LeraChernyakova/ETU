import Swal from 'sweetalert2';
import {Injectable} from "@angular/core";

@Injectable({
  providedIn: 'root'
})

export class Alert {
  success(text: string) {
    Swal.fire('Успешно!', text, 'success');
  }

  error(text: string) {
    Swal.fire('Ошибка!', text, 'error')
  }

  warning(text: string) {
    Swal.fire('Предупреждение!', text, 'warning')
  }

  async delete(text: string): Promise<boolean> {
    const result = await Swal.fire({
      title: 'Вы уверены?',
      text: text,
      icon: 'warning',
      showCancelButton: true,
      confirmButtonText: 'Да',
      cancelButtonText: 'Нет',
    });
    if (result.isConfirmed) {
      return true;
    }
    else if (result.isDismissed) {
      return false;
    }
    return false;
  }
}
