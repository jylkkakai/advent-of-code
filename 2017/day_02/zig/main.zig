const std = @import("std");
const print = @import("std").debug.print;
const data = @embedFile("input.txt");
// const data = @embedFile("example.txt");

pub fn main() !void {
    var lines = std.mem.tokenize(u8, data, "\n");
    var sum1: u32 = 0;
    var sum2: u32 = 0;
    print("Hello, World!\n", .{});
    while (lines.next()) |line| {
        var tokens1 = std.mem.tokenize(u8, line, "\t");
        var tokens2 = std.mem.tokenize(u8, line, "\t");
        var line_max: u32 = 0;
        var line_min: u32 = 1000000;
        var found = false;

        while (tokens1.next()) |token| {
            var tokeni: u32 = 0;
            tokeni = try std.fmt.parseInt(u32, token, 10);
            if (tokeni > line_max) {
                line_max = tokeni;
            }
            if (tokeni < line_min) {
                line_min = tokeni;
            }
            while (!found and tokens2.peek() != null) {
                const rtoken = tokens2.next().?;
                var rtokeni: u32 = 0;
                rtokeni = try std.fmt.parseInt(u32, rtoken, 10);
                if (rtokeni == tokeni) continue;
                if (tokeni % rtokeni == 0) {
                    sum2 += tokeni / rtokeni;
                    found = true;
                }
                if (rtokeni % tokeni == 0) {
                    sum2 += rtokeni / tokeni;
                    found = true;
                }
            }
            tokens2.reset();
        }
        sum1 += line_max - line_min;
        // break;
    }
    print("Part 1: {d}\n", .{sum1});
    print("Part 2: {d}\n", .{sum2});
}
