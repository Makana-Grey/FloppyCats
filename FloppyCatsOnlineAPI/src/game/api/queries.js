import Router from 'koa-router'
import {
    acceptedPlayers,
    searchPlayer,
    getPlayerPoint,
} from '../logic/playersQueries.js'

const router = new Router()

/**
 * @returns {String[]}
 */
router.get('/all', (ctx, next) => {
    ctx.response.status = 200
    ctx.response.body = acceptedPlayers()

    next()
})

/**
 * @param {{query: String}}
 * @returns {String}
 */
router.post('/search', (ctx, next) => {
    ctx.response.status = 200
    ctx.response.body = searchPlayer(ctx.request.body.query)

    next()
})

/**
 * @param {{name: String}}
 * @returns {{ip: String; port: Number}}
 */
router.post('/point', (ctx, next) => {
    ctx.response.status = 200
    ctx.response.body = getPlayerPoint(ctx.request.body.name)

    next()
})

export default router.routes()
