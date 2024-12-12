const std = @import("std");
const print = @import("std").debug.print;
const datar = @embedFile("input.txt");

pub fn main() void {
    const data = datar[0 .. datar.len - 2];
    var sum1: i32 = 0;
    var sum2: i32 = 0;
    var half_len: u64 = 0;
    var second_i: u64 = 0;
    half_len = data.len / 2;
    sum1 += if (data[0] == data[data.len - 1]) data[0] - 48 else 0;
    sum2 += if (data[half_len - 1] == data[data.len - 1]) data[data.len - 1] - 48 else 0;
    // print("{d}\n", .{sum1});
    for (0..data.len - 1) |i| {
        second_i = if (i >= half_len) @as(u64, i) - half_len else @as(u64, i) + half_len;
        if (data[i] == data[i + 1]) sum1 += data[i] - 48;
        if (data[i] == data[second_i]) sum2 += data[i] - 48;
    }
    print("Part 1: {d}\n", .{sum1});
    print("Part 2: {d}\n", .{sum2});
}
