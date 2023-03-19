import { Player, players } from '../data/players.js'

/**
 * @param {{token: String}} key
 * @returns {Player}
 */
export function getPlayer(key) {
    return players.data.find(({ token }) => key?.token === token)
}
