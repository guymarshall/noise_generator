use clap::Parser;
use rand::RngExt;
use std::fs::{self, File};
use std::io::{self, BufWriter, Write, stdout};
use std::path::Path;
use std::process::{Command, exit};

// TODO: make README.md

#[derive(Parser)]
#[command(rename_all = "snake_case")]
struct Cli {
    #[arg(long)]
    frame_count: i32,

    #[arg(long)]
    frames_per_second: i32,

    #[arg(long)]
    width: usize,

    #[arg(long)]
    height: usize,
}

fn run_ffmpeg(frames_per_second: i32) -> io::Result<()> {
    #[cfg(target_os = "windows")]
    let program: &str = "ffmpeg.exe";
    #[cfg(not(target_os = "windows"))]
    let program: &str = "ffmpeg";

    let status: std::process::ExitStatus = Command::new(program)
        .arg("-y")
        .arg("-framerate")
        .arg(frames_per_second.to_string())
        .arg("-i")
        .arg("output-%d.ppm")
        .arg("output.mp4")
        .status()?;

    if !status.success() {
        return Err(io::Error::other(format!(
            "ffmpeg exited with status {}",
            status
        )));
    }

    Ok(())
}

fn main() {
    let arguments: Cli = Cli::parse();

    let frame_count: i32 = arguments.frame_count;
    let frames_per_second: i32 = arguments.frames_per_second;
    let width: usize = arguments.width;
    let height: usize = arguments.height;

    let mut random_number_generator: rand::prelude::ThreadRng = rand::rng();

    let row_length: usize = width * 3;
    let mut row_buffer: Vec<u8> = vec![0u8; row_length];

    (0..frame_count).for_each(|frame: i32| {
        let filename: String = format!("output-{}.ppm", frame);
        let file: File = File::create(Path::new(&filename)).unwrap();
        let mut writer: BufWriter<File> = BufWriter::new(file);

        writeln!(writer, "P6").unwrap();
        writeln!(writer, "{} {}", width, height).unwrap();
        writeln!(writer, "{}", 255).unwrap();

        for _y in 0..height {
            let mut i: usize = 0;
            while i + 2 < row_length {
                let random_number: u32 = random_number_generator.random();
                row_buffer[i] = (random_number & 0xFF) as u8;
                row_buffer[i + 1] = ((random_number >> 8) & 0xFF) as u8;
                row_buffer[i + 2] = ((random_number >> 16) & 0xFF) as u8;
                i += 3;
            }
            while i < row_length {
                row_buffer[i] = (random_number_generator.random::<u32>() & 0xFF) as u8;
                i += 1;
            }
            writer.write_all(&row_buffer).unwrap();
        }

        writer.flush().unwrap();

        let percent_complete: f64 = 100.0 * (frame + 1) as f64 / frame_count as f64;
        print!("\r{:.6}%", percent_complete);
        stdout().flush().unwrap();
    });

    println!();

    run_ffmpeg(frames_per_second).unwrap_or_else(|e: io::Error| {
        eprintln!("ffmpeg failed: {}", e);
        exit(1);
    });

    (0..frame_count).for_each(|frame: i32| {
        let filename: String = format!("output-{}.ppm", frame);
        let path: &Path = Path::new(&filename);
        let _ = fs::remove_file(path);
    });
}
