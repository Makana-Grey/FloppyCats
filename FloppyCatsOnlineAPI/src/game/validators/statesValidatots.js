/**
 * @param {{token: String; isPlay: Boolean}} state
 * @returns {Boolean}
 */
export function isValidToMutatePlay(state) {
    return state && state.token && state.isPlay !== undefined
}

/**
 * @param {{token: String; isPublic: Boolean}} state
 * @returns {Boolean}
 */
export function isValidToMutatePublic(state) {
    return state && state.token && state.isPublic !== undefined
}
