#pragma once

enum class Command {
    unknown,
    move_up,
    move_down,
    move_left,
    move_right,
    exit,
    save,
    restart,
    load
};

struct InputMessage {
    Command command = Command::unknown;
};