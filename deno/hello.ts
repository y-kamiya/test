// https://qiita.com/niwasawa/items/a4e695c4a5ecd8ce69f1
import { copy } from "https://deno.land/std@0.101.0/io/util.ts"

const str = "hello"
console.log(str)

const names = Deno.args
for (const name of names) {
    console.log(name)
    const file = await Deno.open(name)
    await copy(file, Deno.stdout)
    file.close()
}


const url = "https://deno.land/std@0.101.0/io/util.ts"
const res = await fetch(url)
const body = new Uint8Array(await res.arrayBuffer())
await Deno.stdout.write(body)
