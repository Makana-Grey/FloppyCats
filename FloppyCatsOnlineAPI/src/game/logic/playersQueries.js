import { players } from '../data/players.js'

/**
 * @returns {String[]}
 */
export function acceptedPlayers() {
    const result = []
    let count = 5

    for (let i = 0; i < players.data.length; i++) {
        const player = players.data[i]

        if (!player.isPlay && player.isPublic) {
            if (count--) {
                result.push(player.name)
            } else {
                break
            }
        }
    }

    return result
}

/**
 * @param {String} query
 * @returns {String}
 */
export function searchPlayer(query) {
    const player = players.data
        .filter(({ isPlay }) => !isPlay)
        .find(({ name }) => name === query)
    return player?.name || null
}

/**
 * @param {Scting} name
 * @returns {{ip: String; port: Number}}
 */
export function getPlayerPoint(name) {
    const player = players.data
        .filter(({ isPlay }) => !isPlay)
        .find((p) => p.name === name)

    return player ? { ip: player.ip, port: player.port } : null
}
