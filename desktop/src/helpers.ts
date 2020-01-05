
import path from 'path'

export function staticFile(...args: string[]) {
    return path.join(process.cwd(), 'static', ...args)
}