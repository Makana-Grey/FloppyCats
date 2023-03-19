import { getPlayer } from './playerGetter.js'
import {
    isValidToMutatePlay,
    isValidToMutatePublic,
} from '../validators/statesValidatots.js'

/**
 * @param {{token: String; isPlay: Boolean}} state
 * @returns {Boolean}
 */
export function setIsPlay(state) {
    try {
        if (isValidToMutatePlay(state)) {
            const player = getPlayer(state)
            if (player) {
                player.isPlay = state.isPlay
                return true
            }
        }
    } catch (e) {
        console.log(e)
    }
    return false
}

/**
 * @param {{token: String; isPublic: Boolean}} state
 * @returns {Boolean}
 */
export function setIsPublic(state) {
    try {
        if (isValidToMutatePublic(state)) {
            const player = getPlayer(state)
            if (player) {
                player.isPublic = state.isPublic
                return true
            }
        }
    } catch (e) {
        console.log(e)
    }
    return false
}
