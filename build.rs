#![allow(unused_assignments)]
use std::env;

fn main() {
  let target = env::var("CARGO_CFG_TARGET_ARCH")
    .expect("CARGO_CFG_TARGET_ARCH was not set");
  let mut triple = "none-linux-ouma";

  match target.as_str() {
    | "aarch64" => triple = "aarch64-linux-ouma",
    | "x86_64" => triple = "x86_64-linux-ouma",
    | _ => panic!("Platform is not supported")
  }

  let machine_include = format!("include/{}", triple);
  let target_cflags = format!("--target={}", triple);

  println!("cargo:rerun-if-changed=third_party/dlmalloc/dlmalloc.c");
  cc::Build::new()
    .compiler("clang")
    .file("third_party/dlmalloc/dlmalloc.c")
    .flag(&target_cflags)
    .flag("-nostdlibinc")
    .flag("-ffreestanding")
    .flag("-ftls-model=initial-exec")
    .flag("-Wall")
    .flag("-Wextra")
    .flag("-Werror")
    .flag("-Wno-null-pointer-arithmetic")
    .flag("-Wno-unused-but-set-variable")
    .include("include")
    .include(machine_include)
    .compile("dlmalloc");
}
