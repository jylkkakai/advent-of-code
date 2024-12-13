const std = @import("std");
const print = @import("std").debug.print;

const Pos = struct { x: i32 = 0, y: i32 = 0, val: u32 };
const Spiral = struct { pos: Pos, dir: u8 = 0, maxr: i32 = 0, maxu: i32 = 0, minl: i32 = 0, mind: i32 = 0 };

fn find_pos_val(arr: *std.ArrayList(Pos), pos: Pos) u32 {
    for (arr.items) |p| {
        if (pos.x == p.x and pos.y == p.y) return p.val;
    }
    return 0;
}

fn get_adj_sum(arr: *std.ArrayList(Pos), pos: Pos) u32 {
    var sum: u32 = 0;
    var i: i32 = -1;
    var j: i32 = -1;
    while (i < 2) : (i += 1) {
        while (j < 2) : (j += 1) {
            sum += find_pos_val(arr, Pos{ .x = pos.x + i, .y = pos.y + j, .val = 0 });
        }
        j = -1;
    }

    return sum;
}

pub fn main() !void {
    print("Hello, World!\n", .{});

    var gpa = std.heap.GeneralPurposeAllocator(.{}){};
    const allocator = gpa.allocator();

    var arr = std.ArrayList(Pos).init(allocator);
    defer arr.deinit();

    // const number = 2;
    const number = 265149;
    var spiral = Spiral{ .pos = Pos{ .x = 0, .y = 0, .val = 1 } };
    try arr.append(spiral.pos);
    var found = false;

    for (1..number) |_| {
        switch (spiral.dir) {
            0 => {
                spiral.pos.x += 1;
                if (spiral.pos.x > spiral.maxr) {
                    spiral.maxr = spiral.pos.x;
                    spiral.dir = 1;
                }
                if (!found) {
                    spiral.pos.val = get_adj_sum(&arr, spiral.pos);
                    try arr.append(spiral.pos);
                }
            },
            1 => {
                spiral.pos.y += 1;
                if (spiral.pos.y > spiral.maxu) {
                    spiral.maxu = spiral.pos.y;
                    spiral.dir = 2;
                }
                if (!found) {
                    spiral.pos.val = get_adj_sum(&arr, spiral.pos);
                    try arr.append(spiral.pos);
                }
            },
            2 => {
                spiral.pos.x -= 1;
                if (spiral.pos.x < spiral.minl) {
                    spiral.minl = spiral.pos.x;
                    spiral.dir = 3;
                }
                if (!found) {
                    spiral.pos.val = get_adj_sum(&arr, spiral.pos);
                    try arr.append(spiral.pos);
                }
            },
            3 => {
                spiral.pos.y -= 1;
                if (spiral.pos.y < spiral.mind) {
                    spiral.mind = spiral.pos.y;
                    spiral.dir = 0;
                }
                if (!found) {
                    spiral.pos.val = get_adj_sum(&arr, spiral.pos);
                    try arr.append(spiral.pos);
                }
            },
            else => unreachable,
        }
        if (spiral.pos.val > number) found = true;
    }

    print("Part 1: {d} + {d} = {d}\n", .{ spiral.pos.x, spiral.pos.y, @abs(spiral.pos.x) + @abs(spiral.pos.y) });
    print("Part 2: {d}\n", .{arr.items[arr.items.len - 1].val});
}
